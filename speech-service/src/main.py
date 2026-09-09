import os
import platform
import socket
from polars import struct
from transformers import AutoProcessor, SeamlessM4Tv2ForSpeechToSpeech

SOCKET_PATH = "/tmp/ml_service.sock"


def translate_audio(audio,processor,model):
   inputs = processor(audio, return_tensors="pt",sample_rate=16000)
   outputs = model.generate(**inputs,target_lang="hi")

   return outputs[0].cpu().numpy().squeeze()


def main():


  processor = AutoProcessor.from_pretrained(
      "facebook/seamless-m4t-v2-large"
  )

  model = SeamlessM4Tv2ForSpeechToSpeech.from_pretrained(
      "facebook/seamless-m4t-v2-large"
  )

  if os.path.exists(SOCKET_PATH):
      os.remove(SOCKET_PATH)

  server = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

  server.bind(SOCKET_PATH)
  server.listen(1)

  print (f"Server listening on {SOCKET_PATH}")

  conn , _ = server.accept()
  print("Client connected")


  while True:
     header = conn.recv(4)
     audio_size = struct.unpack('!I', header)[0]
     audio_data = conn.recv(audio_size)


     translated_audio = translate_audio("test.wav",processor,model)

     result = translated_audio.astype("float32").tobytes()

     conn.sendall(struct.pack('!I', len(result)))
     conn.sendall(result)

if __name__ == "__main__":
    main()
