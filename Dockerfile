FROM qmkfm/base_container

WORKDIR /qmk_firmware
COPY . .

CMD make all:all