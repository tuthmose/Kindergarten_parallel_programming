export CUDA=/usr/local/cuda-10.0/
export PATH=./:/usr/local/offload/bin:/usr/local/offload/nvptx-none/bin:$CUDA/bin:$PATH
export COMPILER_PATH=/usr/local/offload/bin:/usr/local/offload/nvptx-none/bin:$CUDA/bin:$PATH

export LIBRARY_PATH=/usr/local/offload/lib:/usr/local/offload/lib64:/usr/local/offload/nvptx-none/lib:$CUDA/lib64
export LD_LIBRARY_PATH=/usr/local/offload/lib:/usr/local/offload/lib64:/usr/local/offload/nvptx-none/lib:$CUDA/lib64

export CPATH=/usr/local/offload/include:/usr/local/offload/nvptx-none/include:$CUDA/include
export C_INCLUDE_PATH=/usr/local/offload/include:/usr/local/offload/nvptx-none/include:$CUDA/include
export CPLUS_INCLUDE_PATH=/usr/local/offload/include:/usr/local/offload/nvptx-none/include:$CUDA/include
export OBJC_INCLUDE_PATH=/usr/local/offload/include:/usr/local/offload/nvptx-none/include:$CUDA/include

export CC=/usr/local/offload/bin/gcc
export CXX=/usr/local/offload/bin/g++
export FC=/usr/local/offload/bin/gfortran
export CPP=/usr/local/offload/bin/cpp

export MANPATH=/usr/local/offload/share/man:${MANPATH}
