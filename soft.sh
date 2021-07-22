git pull
sh clean.sh

cd sw
pwd
make

cd ../tb
pwd
make

./sctop ../sw/app.elf