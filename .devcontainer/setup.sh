# Take ownership of the workdir/ directory
sudo chown -R user:user /workdir/

# Initialize the west repository in the 'app' subdirectory
west init -l app

# Make sure the workspace contains Git repositories matching the projects in the manifest file
west update

# Export Zephyr-specific build system metadata to the 'app' directory
west zephyr-export

# Override the ZEPHYR_BASE environment variable
sudo echo 'export ZEPHYR_BASE=/workdir/deps/zephyr' >> ~/.bashrc
sudo source ~/.bashrc

# Install Python dependencies required by Zephyr
pip install -r deps/zephyr/scripts/requirements.txt

# Install Python dependencies required by MCUBoot
pip install -r deps/bootloader/mcuboot/scripts/requirements.txt

# Copy .vscode to outer directory
cp -r app/.vscode .
