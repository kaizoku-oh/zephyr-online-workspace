# Initialize the west repository in the 'app' subdirectory
sudo west init -l app

# Make sure the workspace contains Git repositories matching the projects in the manifest file
sudo west update

# Export Zephyr-specific build system metadata to the 'app' directory
sudo west zephyr-export

# Install Python dependencies required by Zephyr
pip install -r deps/zephyr/scripts/requirements.txt

# Install Python dependencies required by MCUBoot
pip install -r deps/bootloader/mcuboot/scripts/requirements.txt

# Copy .vscode to outer directory
sudo cp -r app/.vscode .
