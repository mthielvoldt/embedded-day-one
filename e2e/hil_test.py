import os
import re
import time
import serial
import pytest

SERIAL_PORT = os.environ.get("HIL_SERIAL_PORT", "/dev/ttyACM0")
BAUDRATE = 115200
READ_TIMEOUT = 0.2


def open_port():
    ser = serial.Serial(
        SERIAL_PORT,
        BAUDRATE,
        timeout=READ_TIMEOUT,
        write_timeout=1.0,
    )

    # Give the RP2040 time after open (CDC reset behavior)
    time.sleep(0.5)

    ser.reset_input_buffer()
    ser.reset_output_buffer()

    return ser


def test_report_version_hil():
    ser = open_port()

    try:
        # Send bogus bytes
        ser.write(b'n\n')
        ser.flush()

        # Give firmware time to react (if it's going to)
        time.sleep(0.5)

        response = ser.read(64)

        assert response == b"", (
            f"Expected no response to garbage, got: {response!r}"
        )

        # Send request for version
        ser.write(b'v')
        ser.flush()

        time.sleep(0.5)

        # If your protocol is line-based:
        version = ser.readline()

        assert version, "No version response received"

        # Example: match semver like 1.2.3 or 1.2.3+12345678
        version_str = version.decode().strip()

        assert ("RP2040" in version_str), (
            f"Invalid version format: {version_str}"
        )

    finally:
        ser.close()
