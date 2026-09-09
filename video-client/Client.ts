import { spawn } from "node:child_process";
import WebSocket from "ws";

const SERVER_URL = "ws://127.0.0.1:8080";

const ws = new WebSocket(SERVER_URL);

ws.on("open", () => {
    console.log("Connected to C++ video server");


    const ffmpeg = spawn("ffmpeg", [
        "-f", "avfoundation",

        "-framerate", "30",

        "-video_size", "1280x720",

        "-i", "0:none",

        // Low-latency H264
        "-c:v", "libx264",
        "-preset", "ultrafast",
        "-tune", "zerolatency",

        "-pix_fmt", "yuv420p",

        // Send MPEG-TS through stdout
        "-f", "mpegts",

        "pipe:1"
    ]);

    // FFmpeg outputs encoded video here
    ffmpeg.stdout.on("data", (chunk: Buffer) => {

        if (ws.readyState !== WebSocket.OPEN) {
            return;
        }

        // Send binary WebSocket message
        ws.send(chunk, {
            binary: true
        });

        console.log(`Sent ${chunk.length} bytes`);
    });


    // FFmpeg diagnostic output
    ffmpeg.stderr.on("data", (data: Buffer) => {
        console.log(
            `[FFmpeg] ${data.toString()}`
        );
    });


    ffmpeg.on("close", (code) => {
        console.log(
            `FFmpeg exited with code ${code}`
        );

        ws.close();
    });


    ws.on("close", () => {
        console.log("WebSocket disconnected");

        ffmpeg.kill("SIGTERM");
    });


    ws.on("error", (error) => {
        console.error(
            "WebSocket error:",
            error
        );

        ffmpeg.kill("SIGTERM");
    });
});


ws.on("error", (error) => {
    console.error(
        "Could not connect:",
        error
    );
});