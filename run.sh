set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

BIN=/tmp/bin

mkdir -p "${BIN}"

echo " "
echo -e "${GREEN}Re-compiling...${NC}"
clang++ -std=c++17 -O3 -Werror  main.cc -o "${BIN}/mtg.out"

echo -e "${GREEN}Running!${NC}"
"${BIN}/mtg.out"
