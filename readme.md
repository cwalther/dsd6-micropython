# MicroPython for DS-D6

This is an external board definition to build MicroPython for the DS-D6 fitness tracker, based on the work done at [fanoush/ds-d6](https://github.com/fanoush/ds-d6).
Refer to that repository and its wiki for details.
In particular, you need to first install the patched Desay bootloader and then the Adafruit bootloader as detailed [there](https://github.com/fanoush/ds-d6/tree/master/micropython).

## How to build

```
git submodule update --init lib/micropython
make -C lib/micropython/mpy-cross
lib/micropython/ports/nrf/drivers/bluetooth/download_ble_stack.sh s132_nrf52_6_1_1
cd boards/DSD6
make port-submodules
make
```

To get a zip file that can be flashed via the Adafruit bootloader either over Bluetooth using nRF Connect or over serial using adafruit-nrfutil:
```
make zip
```

To flash the zip file over serial using adafruit-nrfutil:
```
make NRFUTIL_PORT=/dev/... deploy
```

## How to use

### Bootloader

To enter the bootloader for serial DFU:
```python
import machine
machine.bootloader()
# or
machine.bootloader(False)
```

To enter the bootloader for Bluetooth OTA DFU (look for device “AdaDFU”):
```python
import machine
machine.bootloader(True)
```

### Display

To use the display in landscape orientation:

```python
import machine, ssd1306
display = ssd1306.SSD1306_SPI(128, 32, machine.SPI(0), machine.Pin(28), machine.Pin(4), machine.Pin(29))
display.write_cmd(0xDA); display.write_cmd(0x12)
display.write_cmd(0xC0)

display.rect(0, 0, display.width, display.height, 1)
display.text('Hello World!', 16, 12, 1)
display.show()
```
