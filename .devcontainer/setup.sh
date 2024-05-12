# Take ownership of the workdir/ directory
echo "[setup.sh] Taking ownership of the workdir/ directory"
sudo chown -R user:user /workdir/

# Initialize the west repository in the 'app' subdirectory
echo "[setup.sh] Initializing the west repository in the 'app' subdirectory"
west init -l app

# Make sure the workspace contains Git repositories matching the projects in the manifest file
echo "[setup.sh] Updating west repository"
west update

# Export Zephyr-specific build system metadata to the 'app' directory
echo "[setup.sh] Exporting Zephyr-specific build system metadata to the 'app' directory"
west zephyr-export

# Override the ZEPHYR_BASE environment variable
echo "[setup.sh] Overriding the 'ZEPHYR_BASE' environment variable"
sudo echo 'export ZEPHYR_BASE=/workdir/deps/zephyr' >> ~/.bashrc
sudo source ~/.bashrc

# Install Python dependencies required by Zephyr
echo "[setup.sh] Installing Python dependencies required by Zephyr"
pip install -r deps/zephyr/scripts/requirements.txt

# Install Python dependencies required by MCUBoot
echo "[setup.sh] Installing Python dependencies required by MCUBoot"
pip install -r deps/bootloader/mcuboot/scripts/requirements.txt

# Copy .vscode to outer directory
echo "[setup.sh] Copying .vscode to outer workspace directory"
if [ -d ".vscode" ]; then
    echo "[setup.sh] .vscode already exists in outer workspace directory"
else
    cp -r app/.vscode .
fi
