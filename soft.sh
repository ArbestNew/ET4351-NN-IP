git pull
sh clean.sh

cd sw
pwd
make | tee ../soft_sw_make_result

cd ../tb
pwd
make | tee ../soft_tb_make_result

./sctop ../sw/app.elf | tee ../soft_sim_result