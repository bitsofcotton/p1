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
	@rm -rf pp3n pp3n32
all:	pp3n pp3n32
pp3n:
	${CXX} ${CXXFLAGS} -static -o pp3n pp3.cc
pp3n32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o pp3n32 pp3.cc
pp3n64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o pp3n64 pp3.cc

