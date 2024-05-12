# zephyr-online-workspace
A Zephyr RTOS codespace based on devcontainer

## Usage

```bash
# Make sure the zephyr path is pointing to your zephyr repo
user@480c36b20b00:/workdir$ echo $ZEPHYR_BASE
/workdir/deps/zephyr

# Make sure the build is clean
user@480c36b20b00:/workdir$ rm -rf /workdir/app/build

# Build the app
user@480c36b20b00:/workdir$ west build /workdir/app -d /workdir/app/build -p auto -b nucleo_f767zi

# Flash the app
user@480c36b20b00:/workdir$ west flash -d /workdir/app/build

# Debug the app with gdb
user@480c36b20b00:/workdir$ west debug --build-dir app/build/
```

## Limitation
`ZEPHYR_BASE` environment variable is hard coded in the docker image

## ✅ ToDo

- [x] Build an STM32 app

- [x] Flash app using openocd

- [ ] Debug app using vscode cortex-debug

- [ ] Restructure workspace to be compatible with the hard coded `ZEPHYR_BASE` path
