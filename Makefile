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
	${CXX} ${CXXFLAGS} -static -o p1 pp3.cc
p1-32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p1-32 pp3.cc
p1-64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o p1-64 pp3.cc
p1c:
	${CXX} ${CXXFLAGS} -D_CHAIN_ -static -o p1c pp3.cc
p1c32:
	${CXX} ${CXXFLAGS} -D_CHAIN_ -static -D_FLOAT_BITS_=32 -o p1c32 pp3.cc
p1c64:
	${CXX} ${CXXFLAGS} -D_CHAIN_ -static -D_FLOAT_BITS_=64 -o p1c64 pp3.cc

