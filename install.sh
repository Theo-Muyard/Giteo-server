#!bin/bash

INSTALL_DIR="$HOME/.giteo-server"
BIN_DIR="$INSTALL_DIR/bin"
SETTINGS_DIR="$INSTALL_DIR/settings"
LIB_DIR="$INSTALL_DIR/libs"

if [ -d "$INSTALL_DIR" ]; then
	echo "Giteo-server is already installed."
	exit 0
fi

echo "Installing giteo-server..."

mkdir -p $BIN_DIR
mkdir -p $SETTINGS_DIR
mkdir -p $LIB_DIR

make -s json

cp include/cJSON/build/libcjson.so.1 "$LIB_DIR/libcjson.so.1"

make -s

cp bin/giteo-server "$BIN_DIR"
cp -r bin/commands/ "$BIN_DIR/commands"
cp src/protocole.json "$SETTINGS_DIR/protocole.json"

make -s fclean

if [ "$SHELL" = "/bin/zsh" ]; then
	RC="$HOME/.zshrc"
else
	RC="$HOME/.bashrc"
fi

echo 'export PATH="$HOME/.giteo-server/bin:$PATH"' >> "$RC"
echo "Installing done."