export VITASDK=/usr/local/vitasdk
export PATH=$VITASDK/bin:$PATH


cd kernel/
cmake .
make install

cd ../spoofer/
make clean
make

cd ../user/
cmake .
make install

cd ../kmspico/
cmake .
make install

cd ../app/
mv ../kmspico/kmspico.skprx kmspico.skprx
mv ../spoofer/kDump.skprx testkit.skprx
mv ../kernel/kernel.skprx kernel.skprx
mv ../user/user.suprx user.suprx
cmake .
make