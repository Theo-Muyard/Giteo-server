#!bin/bash

UNINSTALL_DIR="$HOME/.giteo-server"

if [ $(basename "$SHELL") = "zsh" ]; then
	RC="$HOME/.zshrc"
else
	RC="$HOME/.bashrc"
fi

if [ -d "$UNINSTALL_DIR" ]; then
	echo "Uninstalling giteo-server..."
	rm -rf $HOME/.giteo-server
	sed -i '/export PATH="\$HOME\/\.giteo-server\/bin:\$PATH"/d' "$RC"
	echo "Done."
	exit 0
fi
echo "Giteo-server is not already installed."