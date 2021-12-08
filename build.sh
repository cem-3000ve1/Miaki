export VITASDK=/usr/local/vitasdk
export PATH=$VITASDK/bin:$PATH


cd kernel/
cmake .
make install

cd ../spoofer_vita/
make clean
make

cd ../spoofer_pstv/
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
mv ../spoofer_vita/kDump.skprx testkit_vita.skprx
mv ../spoofer_pstv/kDump.skprx testkit_pstv.skprx
mv ../kernel/kernel.skprx kernel.skprx
mv ../user/user.suprx user.suprx
cmake .
make
