# Change CRLF to LF in case when Windows has changed it...
find . -type f \( -name "*.sh" \) -exec sed -i 's/\r$//' {} \;

# Builds the KAOSLDR
cd /src/main64/kaosldr
make clean && make

# Builds the 1st program
cd ..
cd programs/program1
make clean && make

# Builds the 2nd program
cd ..
cd ..
cd programs/program2
make clean && make

# Builds the kernel
cd ..
cd ..
cd kernel
make clean && make