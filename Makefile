CXX=	clang++

# compiler flags.
CXXFLAGS+=	-std=c++11
#CXXFLAGS+=	-fopenmp -I/usr/local/include -L/usr/local/lib -lomp
#CXXFLAGS+=	-pg
#CXXFLAGS+=	-Ofast -mtune=native -gfull
CXXFLAGS+=	-Oz -mtune=native -gfull
#CXXFLAGS+=	-Ofast -mno-sse2 -mno-sse -mno-3dnow -mno-mmx -msoft-float -gfull
LDFLAGS+=	-lc++

clean:
	@rm -rf p1 p1-32
all:	p1 p1-32
p1:
	${CXX} ${CXXFLAGS} -static -o p1 p1.cc
p1-32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p1-32 p1.cc

