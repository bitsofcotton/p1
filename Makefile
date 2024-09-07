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
	@rm -rf p1 p1-32 pp3 pp3-32 pp3n pp3n32
all:	p1 p1-32 pp3 pp3-32 pp3n pp3n32
p1:
	${CXX} ${CXXFLAGS} -static -o p1 p1.cc
p1-32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o p1-32 p1.cc
p1-64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o p1-64 p1.cc
pp3:
	${CXX} ${CXXFLAGS} -static -o pp3 pp3.cc
pp3-32:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=32 -o pp3-32 pp3.cc
pp3-64:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=64 -o pp3-64 pp3.cc
pp3n:
	${CXX} ${CXXFLAGS} -static -D_MULTI_ -o pp3n pp3.cc
pp3n32:
	${CXX} ${CXXFLAGS} -static -D_MULTI_ -D_FLOAT_BITS_=32 -o pp3n32 pp3.cc
pp3n64:
	${CXX} ${CXXFLAGS} -static -D_MULTI_ -D_FLOAT_BITS_=64 -o pp3n64 pp3.cc

