echo "# this shell script is used to download, configure and install zsh and oh-my-zsh in a non-priviledged environment"
echo "# meanwhile, the script will automatically install 2 plugins: zsh-syntax-highlighting&zsh-autosuggestions"

sleep 3s

WORKSPACE_OLD=$(cd "$(dirname "$0")" && pwd)
echo "mkdir zsh-installation" |sh
WORKSPACE=$WORKSPACE_OLD/zsh-installation
cd $WORKSPACE

# build and install ncurses
wget ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.1.tar.gz
tar xvf ncurses-6.1.tar.gz
rm *.tar.gz
mv ncurses* ncurses
cd $WORKSPACE/ncurses
./configure --prefix=$HOME/local CXXFLAGS="-fPIC" CFLAGS="-fPIC"
make -j && make install
cd $WORKSPACE

# build and install zsh
wget -O zsh.tar.xz https://sourceforge.net/projects/zsh/files/latest/download
tar xvf zsh.tar.xz
rm *.tar.*
mv zsh* zsh
cd $WORKSPACE/zsh
./configure --prefix="$HOME/local" \
    CPPFLAGS="-I$HOME/local/include" \
    LDFLAGS="-L$HOME/local/lib"
make -j && make install

# env var configure & zsh auto-launch
echo 'export PATH=$HOME/local/bin:$PATH' >> ~/.profile
echo "exec zsh" >> ~/.profile
#echo "source ~/.profile" |sh
echo "source ~/.profile"|zsh
echo "---------------------env var config done---------------------"

# install plugins
wget https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh
chmod +x install.sh
echo 'sh install.sh' |sh
echo 'git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions' |sh
echo 'git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting' |sh
echo "sed -i 's/plugins=(git/plugins=(git\ zsh-autosuggestions\ zsh-syntax-highlighting/g' ~/.zshrc" |sh
echo "sed -i 's/robbyrussell/ys/g' ~/.zshrc" |sh
echo "source ~/.zshrc"|zsh
cd $WORKSPACE_OLD
echo "----------------------install plugins done---------------------"
echo "---------------------installation down------------------------"
