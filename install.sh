#!bin/bash

INSTALL_DIR="$HOME/.giteo-server"
BIN_DIR="$INSTALL_DIR/bin"
SETTINGS_DIR="$INSTALL_DIR/settings"

if [ -d "$INSTALL_DIR" ]; then
	echo "Giteo-server is already installed."
	exit 0
fi

echo "Installing giteo-server..."

mkdir -p $BIN_DIR
mkdir -p $SETTINGS_DIR

make -s

cp bin/giteo-server "$BIN_DIR"
cp -r bin/commands/ "$BIN_DIR/commands"
cp src/protocole.json "$SETTINGS_DIR/protocole.json"

make -s fclean

echo 'export PATH="$HOME/.giteo-server/bin:$PATH"' >> ~/.bashrc
source ~/.zshrc
echo "Done."