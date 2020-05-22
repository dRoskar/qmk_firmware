@ECHO OFF
docker cp .\keyboards\ergodox_ez\keymaps\surgeon-general\keymap.c qmk:qmk_firmware/keyboards/ergodox_ez/keymaps/surgeon-general/
docker start -i qmk
docker cp qmk:qmk_firmware/ergodox_ez_surgeon-general.hex ./..
PAUSE