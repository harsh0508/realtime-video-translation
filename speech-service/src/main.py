import platform


def main():

    print("=" * 40)
    print("Speech Translation Service")
    print("=" * 40)

    print()
    print("Platform:", platform.system())

    print()
    print("Pipeline:")

    print("""
Audio
  ↓
ASR
  ↓
English Text
  ↓
IndicTrans2
  ↓
Hindi Text
  ↓
XTTS / IndicF5
  ↓
Hindi Audio
""")


if __name__ == "__main__":
    main()
