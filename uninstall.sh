#!bin/bash

UNINSTALL_DIR="$HOME/.giteo-server"

if [ -d "$UNINSTALL_DIR" ]; then
	echo "Uninstalling giteo-server..."
	rm -rf $HOME/.giteo-server
	sed -i '/export PATH="\$HOME\/\.giteo-server\/bin:\$PATH"/d' ~/.bashrc
	echo "Done."
	exit 0
fi
echo "Giteo-server is not already installed."