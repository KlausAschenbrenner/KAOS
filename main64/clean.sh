# Change CRLF to LF in case when Windows has changed it...
find . -type f \( -name "*.sh" \) -exec sed -i 's/\r$//' {} \;

cd /src/main64/kaosldr
make clean
cd ..
cd programs/program1
make clean
cd ..
cd ..
cd programs/program2
make clean
cd ..
cd ..
cd kernel
make clean