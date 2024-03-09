TARGET=$1
BINARY_DIR=build

make ${BINARY_DIR}/${TARGET}
python check.py ${TARGET}