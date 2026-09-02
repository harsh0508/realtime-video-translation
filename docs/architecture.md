# System Architecture

## High-Level Flow

Video Input

     |
     v

C++ Media Engine

     |
     +-----------------------------+
     |                             |
     v                             v

   Audio                         Video
     |                             |
     v                             |
Speech Service                     |
     |                             |
     v                             |
Hindi Audio                        |
     |                             |
     +-------------+---------------+
                   |
                   v

             Lip Sync Service

                   |
                   v

             Modified Frames

                   |
                   v

              Media Engine

                   |
                   v

               A/V Sync

                   |
                   v

             Encode / Mux

                   |
                   v

                 Output


# Runtime Processes

## Process 1

C++ Media Engine

- FFmpeg
- networking
- stream IDs
- timestamps
- concurrency
- queues
- backpressure
- synchronization
- encoding
- routing


## Process 2

Speech ML Service

ASR
→ Translation
→ TTS


## Process 3

Lip-Sync ML Service

Frames
+
Translated audio
→
lip-synced frames
