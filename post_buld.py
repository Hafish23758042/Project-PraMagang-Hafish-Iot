import os
import sys


firmware_path = os.environ.get("PIOENV")
if firmware_path:
    firmware_bin = os.path.join(
        ".pio", "build", firmware_path, "firmware.bin")
    
    print("Firmware binary path:")
    print(firmware_bin)