import platform


def main():

    print("=" * 40)
    print("Lip Sync Service")
    print("=" * 40)

    print()
    print("Platform:", platform.system())

    print("""
Input:

Original Frames
      +
Translated Hindi Audio

      ↓

   Lip-Sync Model

      ↓

Modified Frames
""")

    print("Initial model target: MuseTalk")


if __name__ == "__main__":
    main()
