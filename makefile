#
# 'make depend' uses makedepend to automatically generate dependencies
#               (dependencies are added to end of Makefile)
# 'make'        build executable
# 'make clean'  removes all .o and executable files
#

CC := c++
CFLAGS := -Wall -g2 -O2 -std=c++11 -fno-strict-aliasing
ROOT_DIR := .
INCLUDES :=
LFLAGS :=
LIBS := -lX11 -lXi -lXmu -lglut -lGLU -lGL -lm
SRCS := $(shell ls -1 $(ROOT_DIR)/src/DGP/*.cpp | sed 's/ /\\ /g') \
        $(shell ls -1 $(ROOT_DIR)/src/DGP/Graphics/*.cpp | sed 's/ /\\ /g') \
        $(shell ls -1 $(ROOT_DIR)/src/*.cpp | sed 's/ /\\ /g')
OBJS := $(SRCS:.cpp=.o)
MAIN := simplify

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: $(MAIN)
	@echo  Compilation finished

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

src/DGP/BinaryInputStream.o: src/DGP/BinaryInputStream.hpp src/DGP/Common.hpp
src/DGP/BinaryInputStream.o: src/DGP/Platform.hpp
src/DGP/BinaryInputStream.o: src/DGP/SymbolVisibility.hpp
src/DGP/BinaryInputStream.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/BinaryInputStream.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/BinaryInputStream.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/BinaryInputStream.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/BinaryInputStream.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/BinaryInputStream.o: /usr/include/fnmatch.h src/DGP/Colors.hpp
src/DGP/BinaryInputStream.o: src/DGP/ColorL.hpp src/DGP/Math.hpp
src/DGP/BinaryInputStream.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/BinaryInputStream.o: /usr/include/features.h
src/DGP/BinaryInputStream.o: /usr/include/stdc-predef.h
src/DGP/BinaryInputStream.o: /usr/include/sys/cdefs.h
src/DGP/BinaryInputStream.o: /usr/include/bits/wordsize.h
src/DGP/BinaryInputStream.o: /usr/include/gnu/stubs.h
src/DGP/BinaryInputStream.o: /usr/include/bits/math-vector.h
src/DGP/BinaryInputStream.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/BinaryInputStream.o: /usr/include/bits/huge_val.h
src/DGP/BinaryInputStream.o: /usr/include/bits/huge_valf.h
src/DGP/BinaryInputStream.o: /usr/include/bits/huge_vall.h
src/DGP/BinaryInputStream.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
src/DGP/BinaryInputStream.o: /usr/include/bits/mathdef.h
src/DGP/BinaryInputStream.o: /usr/include/bits/mathcalls.h
src/DGP/BinaryInputStream.o: src/DGP/ColorL8.hpp src/DGP/ColorRGB.hpp
src/DGP/BinaryInputStream.o: src/DGP/Vector3.hpp src/DGP/Vector2.hpp
src/DGP/BinaryInputStream.o: src/DGP/VectorN.hpp src/DGP/Vector4.hpp
src/DGP/BinaryInputStream.o: src/DGP/ColorRGB8.hpp src/DGP/ColorRGBA.hpp
src/DGP/BinaryInputStream.o: src/DGP/ColorRGBA8.hpp
src/DGP/BinaryInputStream.o: src/DGP/CoordinateFrame3.hpp
src/DGP/BinaryInputStream.o: src/DGP/CoordinateFrameN.hpp
src/DGP/BinaryInputStream.o: src/DGP/RigidTransformN.hpp
src/DGP/BinaryInputStream.o: src/DGP/AffineTransformN.hpp
src/DGP/BinaryInputStream.o: src/DGP/MatrixMN.hpp
src/DGP/BinaryInputStream.o: src/DGP/AddressableMatrix.hpp
src/DGP/BinaryInputStream.o: src/DGP/IteratableMatrix.hpp
src/DGP/BinaryInputStream.o: src/DGP/BasicMatrix.hpp src/DGP/MatrixInvert.hpp
src/DGP/BinaryInputStream.o: src/DGP/MatrixInvertTmpl.hpp src/DGP/Matrix2.hpp
src/DGP/BinaryInputStream.o: src/DGP/Matrix3.hpp src/DGP/Matrix4.hpp
src/DGP/BinaryInputStream.o: src/DGP/AffineTransform2.hpp
src/DGP/BinaryInputStream.o: src/DGP/AffineTransform3.hpp
src/DGP/BinaryInputStream.o: src/DGP/RigidTransform2.hpp
src/DGP/BinaryInputStream.o: src/DGP/RigidTransform3.hpp
src/DGP/BinaryInputStream.o: src/DGP/CoordinateFrame2.hpp
src/DGP/BinaryInputStream.o: src/DGP/NamedObject.hpp src/DGP/Plane3.hpp
src/DGP/BinaryInputStream.o: src/DGP/Hyperplane3.hpp src/DGP/HyperplaneN.hpp
src/DGP/BinaryInputStream.o: src/DGP/RayIntersectableN.hpp src/DGP/RayN.hpp
src/DGP/BinaryInputStream.o: src/DGP/Ray3.hpp src/DGP/RayIntersectable3.hpp
src/DGP/BinaryInputStream.o: src/DGP/FilePath.hpp src/DGP/FileSystem.hpp
src/DGP/BinaryInputStream.o: /usr/include/stdio.h /usr/include/bits/types.h
src/DGP/BinaryInputStream.o: /usr/include/bits/typesizes.h
src/DGP/BinaryInputStream.o: /usr/include/libio.h /usr/include/_G_config.h
src/DGP/BinaryInputStream.o: /usr/include/wchar.h
src/DGP/BinaryInputStream.o: /usr/include/bits/stdio_lim.h
src/DGP/BinaryInputStream.o: /usr/include/bits/sys_errlist.h
src/DGP/BinaryOutputStream.o: src/DGP/BinaryOutputStream.hpp
src/DGP/BinaryOutputStream.o: src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/BinaryOutputStream.o: src/DGP/SymbolVisibility.hpp
src/DGP/BinaryOutputStream.o: src/DGP/AtomicInt32.hpp
src/DGP/BinaryOutputStream.o: src/DGP/NumericTypes.hpp
src/DGP/BinaryOutputStream.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/BinaryOutputStream.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/BinaryOutputStream.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/BinaryOutputStream.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/BinaryOutputStream.o: /usr/include/fnmatch.h src/DGP/Colors.hpp
src/DGP/BinaryOutputStream.o: src/DGP/ColorL.hpp src/DGP/Math.hpp
src/DGP/BinaryOutputStream.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/BinaryOutputStream.o: /usr/include/features.h
src/DGP/BinaryOutputStream.o: /usr/include/stdc-predef.h
src/DGP/BinaryOutputStream.o: /usr/include/sys/cdefs.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/wordsize.h
src/DGP/BinaryOutputStream.o: /usr/include/gnu/stubs.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/math-vector.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/huge_val.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/huge_valf.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/huge_vall.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/mathdef.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/mathcalls.h
src/DGP/BinaryOutputStream.o: src/DGP/ColorL8.hpp src/DGP/ColorRGB.hpp
src/DGP/BinaryOutputStream.o: src/DGP/Vector3.hpp src/DGP/Vector2.hpp
src/DGP/BinaryOutputStream.o: src/DGP/VectorN.hpp src/DGP/Vector4.hpp
src/DGP/BinaryOutputStream.o: src/DGP/ColorRGB8.hpp src/DGP/ColorRGBA.hpp
src/DGP/BinaryOutputStream.o: src/DGP/ColorRGBA8.hpp
src/DGP/BinaryOutputStream.o: src/DGP/CoordinateFrame3.hpp
src/DGP/BinaryOutputStream.o: src/DGP/CoordinateFrameN.hpp
src/DGP/BinaryOutputStream.o: src/DGP/RigidTransformN.hpp
src/DGP/BinaryOutputStream.o: src/DGP/AffineTransformN.hpp
src/DGP/BinaryOutputStream.o: src/DGP/MatrixMN.hpp
src/DGP/BinaryOutputStream.o: src/DGP/AddressableMatrix.hpp
src/DGP/BinaryOutputStream.o: src/DGP/IteratableMatrix.hpp
src/DGP/BinaryOutputStream.o: src/DGP/BasicMatrix.hpp
src/DGP/BinaryOutputStream.o: src/DGP/MatrixInvert.hpp
src/DGP/BinaryOutputStream.o: src/DGP/MatrixInvertTmpl.hpp
src/DGP/BinaryOutputStream.o: src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp
src/DGP/BinaryOutputStream.o: src/DGP/Matrix4.hpp
src/DGP/BinaryOutputStream.o: src/DGP/AffineTransform2.hpp
src/DGP/BinaryOutputStream.o: src/DGP/AffineTransform3.hpp
src/DGP/BinaryOutputStream.o: src/DGP/RigidTransform2.hpp
src/DGP/BinaryOutputStream.o: src/DGP/RigidTransform3.hpp
src/DGP/BinaryOutputStream.o: src/DGP/CoordinateFrame2.hpp
src/DGP/BinaryOutputStream.o: src/DGP/NamedObject.hpp src/DGP/Plane3.hpp
src/DGP/BinaryOutputStream.o: src/DGP/Hyperplane3.hpp src/DGP/HyperplaneN.hpp
src/DGP/BinaryOutputStream.o: src/DGP/RayIntersectableN.hpp src/DGP/RayN.hpp
src/DGP/BinaryOutputStream.o: src/DGP/Ray3.hpp src/DGP/RayIntersectable3.hpp
src/DGP/BinaryOutputStream.o: src/DGP/FilePath.hpp src/DGP/FileSystem.hpp
src/DGP/BinaryOutputStream.o: /usr/include/stdio.h /usr/include/bits/types.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/typesizes.h
src/DGP/BinaryOutputStream.o: /usr/include/libio.h /usr/include/_G_config.h
src/DGP/BinaryOutputStream.o: /usr/include/wchar.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/stdio_lim.h
src/DGP/BinaryOutputStream.o: /usr/include/bits/sys_errlist.h
src/DGP/Camera.o: src/DGP/Camera.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/Camera.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/DGP/Camera.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/DGP/Camera.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/Camera.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/Camera.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/Camera.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/DGP/Camera.o: src/DGP/Serializable.hpp src/DGP/IOStream.hpp
src/DGP/Camera.o: src/DGP/BinaryInputStream.hpp src/DGP/Colors.hpp
src/DGP/Camera.o: src/DGP/ColorL.hpp src/DGP/Math.hpp src/DGP/Random.hpp
src/DGP/Camera.o: /usr/include/math.h /usr/include/features.h
src/DGP/Camera.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/DGP/Camera.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/DGP/Camera.o: /usr/include/bits/math-vector.h
src/DGP/Camera.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Camera.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/DGP/Camera.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Camera.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Camera.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/DGP/Camera.o: src/DGP/ColorRGB.hpp src/DGP/Vector3.hpp
src/DGP/Camera.o: src/DGP/Vector2.hpp src/DGP/VectorN.hpp src/DGP/Vector4.hpp
src/DGP/Camera.o: src/DGP/ColorRGB8.hpp src/DGP/ColorRGBA.hpp
src/DGP/Camera.o: src/DGP/ColorRGBA8.hpp src/DGP/CoordinateFrame3.hpp
src/DGP/Camera.o: src/DGP/CoordinateFrameN.hpp src/DGP/RigidTransformN.hpp
src/DGP/Camera.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Camera.o: src/DGP/AddressableMatrix.hpp src/DGP/IteratableMatrix.hpp
src/DGP/Camera.o: src/DGP/BasicMatrix.hpp src/DGP/MatrixInvert.hpp
src/DGP/Camera.o: src/DGP/MatrixInvertTmpl.hpp src/DGP/Matrix2.hpp
src/DGP/Camera.o: src/DGP/Matrix3.hpp src/DGP/Matrix4.hpp
src/DGP/Camera.o: src/DGP/AffineTransform2.hpp src/DGP/AffineTransform3.hpp
src/DGP/Camera.o: src/DGP/RigidTransform2.hpp src/DGP/RigidTransform3.hpp
src/DGP/Camera.o: src/DGP/CoordinateFrame2.hpp src/DGP/NamedObject.hpp
src/DGP/Camera.o: src/DGP/Plane3.hpp src/DGP/Hyperplane3.hpp
src/DGP/Camera.o: src/DGP/HyperplaneN.hpp src/DGP/RayIntersectableN.hpp
src/DGP/Camera.o: src/DGP/RayN.hpp src/DGP/Ray3.hpp
src/DGP/Camera.o: src/DGP/RayIntersectable3.hpp
src/DGP/Camera.o: src/DGP/BinaryOutputStream.hpp src/DGP/TextInputStream.hpp
src/DGP/Camera.o: src/DGP/TextOutputStream.hpp
src/DGP/ColorL8.o: src/DGP/ColorL8.hpp src/DGP/Common.hpp
src/DGP/ColorL8.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/ColorL8.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/ColorL8.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/ColorL8.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/ColorL8.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/ColorL8.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/ColorL8.o: /usr/include/fnmatch.h src/DGP/Math.hpp src/DGP/Random.hpp
src/DGP/ColorL8.o: /usr/include/math.h /usr/include/features.h
src/DGP/ColorL8.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/DGP/ColorL8.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/DGP/ColorL8.o: /usr/include/bits/math-vector.h
src/DGP/ColorL8.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/ColorL8.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/DGP/ColorL8.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/ColorL8.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/ColorL8.o: /usr/include/bits/mathcalls.h src/DGP/ColorL.hpp
src/DGP/ColorL.o: src/DGP/ColorL.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/ColorL.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/DGP/ColorL.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/DGP/ColorL.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/ColorL.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/ColorL.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/ColorL.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/DGP/ColorL.o: src/DGP/Math.hpp src/DGP/Random.hpp /usr/include/math.h
src/DGP/ColorL.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/ColorL.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/ColorL.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/DGP/ColorL.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/ColorL.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/DGP/ColorL.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/ColorL.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/ColorL.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/DGP/ColorRGB8.o: src/DGP/ColorRGB8.hpp src/DGP/Common.hpp
src/DGP/ColorRGB8.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/ColorRGB8.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/ColorRGB8.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/ColorRGB8.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/ColorRGB8.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/ColorRGB8.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/ColorRGB8.o: /usr/include/fnmatch.h src/DGP/ColorL.hpp
src/DGP/ColorRGB8.o: src/DGP/Math.hpp src/DGP/Random.hpp /usr/include/math.h
src/DGP/ColorRGB8.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/ColorRGB8.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/ColorRGB8.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/DGP/ColorRGB8.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/ColorRGB8.o: /usr/include/bits/huge_val.h
src/DGP/ColorRGB8.o: /usr/include/bits/huge_valf.h
src/DGP/ColorRGB8.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/ColorRGB8.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/ColorRGB8.o: /usr/include/bits/mathcalls.h src/DGP/ColorRGB.hpp
src/DGP/ColorRGB8.o: src/DGP/Vector3.hpp src/DGP/Vector2.hpp
src/DGP/ColorRGB8.o: src/DGP/VectorN.hpp src/DGP/Vector4.hpp
src/DGP/ColorRGBA8.o: src/DGP/ColorRGBA8.hpp src/DGP/Common.hpp
src/DGP/ColorRGBA8.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/ColorRGBA8.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/ColorRGBA8.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/ColorRGBA8.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/ColorRGBA8.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/ColorRGBA8.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/ColorRGBA8.o: /usr/include/fnmatch.h src/DGP/ColorL.hpp
src/DGP/ColorRGBA8.o: src/DGP/Math.hpp src/DGP/Random.hpp /usr/include/math.h
src/DGP/ColorRGBA8.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/ColorRGBA8.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/ColorRGBA8.o: /usr/include/gnu/stubs.h
src/DGP/ColorRGBA8.o: /usr/include/bits/math-vector.h
src/DGP/ColorRGBA8.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/ColorRGBA8.o: /usr/include/bits/huge_val.h
src/DGP/ColorRGBA8.o: /usr/include/bits/huge_valf.h
src/DGP/ColorRGBA8.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/ColorRGBA8.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/ColorRGBA8.o: /usr/include/bits/mathcalls.h src/DGP/ColorRGB8.hpp
src/DGP/ColorRGBA8.o: src/DGP/ColorRGBA.hpp src/DGP/ColorRGB.hpp
src/DGP/ColorRGBA8.o: src/DGP/Vector3.hpp src/DGP/Vector2.hpp
src/DGP/ColorRGBA8.o: src/DGP/VectorN.hpp src/DGP/Vector4.hpp
src/DGP/ColorRGBA.o: src/DGP/ColorRGBA.hpp src/DGP/Common.hpp
src/DGP/ColorRGBA.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/ColorRGBA.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/ColorRGBA.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/ColorRGBA.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/ColorRGBA.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/ColorRGBA.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/ColorRGBA.o: /usr/include/fnmatch.h src/DGP/ColorL.hpp
src/DGP/ColorRGBA.o: src/DGP/Math.hpp src/DGP/Random.hpp /usr/include/math.h
src/DGP/ColorRGBA.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/ColorRGBA.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/ColorRGBA.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/DGP/ColorRGBA.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/ColorRGBA.o: /usr/include/bits/huge_val.h
src/DGP/ColorRGBA.o: /usr/include/bits/huge_valf.h
src/DGP/ColorRGBA.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/ColorRGBA.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/ColorRGBA.o: /usr/include/bits/mathcalls.h src/DGP/ColorRGB.hpp
src/DGP/ColorRGBA.o: src/DGP/Vector3.hpp src/DGP/Vector2.hpp
src/DGP/ColorRGBA.o: src/DGP/VectorN.hpp src/DGP/Vector4.hpp
src/DGP/ColorRGBA.o: src/DGP/ColorRGBA8.hpp src/DGP/ColorRGB8.hpp
src/DGP/ColorRGB.o: src/DGP/ColorRGB.hpp src/DGP/Common.hpp
src/DGP/ColorRGB.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/ColorRGB.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/ColorRGB.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/ColorRGB.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/ColorRGB.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/ColorRGB.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/ColorRGB.o: /usr/include/fnmatch.h src/DGP/ColorL.hpp
src/DGP/ColorRGB.o: src/DGP/Math.hpp src/DGP/Random.hpp /usr/include/math.h
src/DGP/ColorRGB.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/ColorRGB.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/ColorRGB.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/DGP/ColorRGB.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/ColorRGB.o: /usr/include/bits/huge_val.h
src/DGP/ColorRGB.o: /usr/include/bits/huge_valf.h
src/DGP/ColorRGB.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/ColorRGB.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/ColorRGB.o: /usr/include/bits/mathcalls.h src/DGP/Vector3.hpp
src/DGP/ColorRGB.o: src/DGP/Vector2.hpp src/DGP/VectorN.hpp
src/DGP/ColorRGB.o: src/DGP/Vector4.hpp src/DGP/ColorRGB8.hpp
src/DGP/ColorRGB.o: src/DGP/Crypto.hpp
src/DGP/Crypto.o: src/DGP/Crypto.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/Crypto.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/DGP/Crypto.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/DGP/Crypto.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/Crypto.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/Crypto.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/Crypto.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/DGP/FilePath.o: src/DGP/FilePath.hpp src/DGP/Common.hpp
src/DGP/FilePath.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/FilePath.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/FilePath.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/FilePath.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/FilePath.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/FilePath.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/FilePath.o: /usr/include/fnmatch.h
src/DGP/FileSystem.o: src/DGP/FileSystem.hpp src/DGP/Common.hpp
src/DGP/FileSystem.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/FileSystem.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/FileSystem.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/FileSystem.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/FileSystem.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/FileSystem.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/FileSystem.o: /usr/include/fnmatch.h /usr/include/sys/stat.h
src/DGP/FileSystem.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/FileSystem.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/FileSystem.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
src/DGP/FileSystem.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/DGP/FileSystem.o: /usr/include/bits/stat.h
src/DGP/Image.o: src/DGP/Image.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/Image.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/DGP/Image.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/DGP/Image.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/Image.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/Image.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/Image.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/DGP/Image.o: src/DGP/IOStream.hpp src/DGP/BinaryInputStream.hpp
src/DGP/Image.o: src/DGP/Colors.hpp src/DGP/ColorL.hpp src/DGP/Math.hpp
src/DGP/Image.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/Image.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/Image.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/Image.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/DGP/Image.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Image.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/DGP/Image.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Image.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Image.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/DGP/Image.o: src/DGP/ColorRGB.hpp src/DGP/Vector3.hpp src/DGP/Vector2.hpp
src/DGP/Image.o: src/DGP/VectorN.hpp src/DGP/Vector4.hpp
src/DGP/Image.o: src/DGP/ColorRGB8.hpp src/DGP/ColorRGBA.hpp
src/DGP/Image.o: src/DGP/ColorRGBA8.hpp src/DGP/CoordinateFrame3.hpp
src/DGP/Image.o: src/DGP/CoordinateFrameN.hpp src/DGP/RigidTransformN.hpp
src/DGP/Image.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Image.o: src/DGP/AddressableMatrix.hpp src/DGP/IteratableMatrix.hpp
src/DGP/Image.o: src/DGP/BasicMatrix.hpp src/DGP/MatrixInvert.hpp
src/DGP/Image.o: src/DGP/MatrixInvertTmpl.hpp src/DGP/Matrix2.hpp
src/DGP/Image.o: src/DGP/Matrix3.hpp src/DGP/Matrix4.hpp
src/DGP/Image.o: src/DGP/AffineTransform2.hpp src/DGP/AffineTransform3.hpp
src/DGP/Image.o: src/DGP/RigidTransform2.hpp src/DGP/RigidTransform3.hpp
src/DGP/Image.o: src/DGP/CoordinateFrame2.hpp src/DGP/NamedObject.hpp
src/DGP/Image.o: src/DGP/Plane3.hpp src/DGP/Hyperplane3.hpp
src/DGP/Image.o: src/DGP/HyperplaneN.hpp src/DGP/RayIntersectableN.hpp
src/DGP/Image.o: src/DGP/RayN.hpp src/DGP/Ray3.hpp
src/DGP/Image.o: src/DGP/RayIntersectable3.hpp src/DGP/BinaryOutputStream.hpp
src/DGP/Image.o: src/DGP/TextInputStream.hpp src/DGP/TextOutputStream.hpp
src/DGP/Image.o: src/DGP/Serializable.hpp src/DGP/FilePath.hpp
src/DGP/Image.o: src/DGP/stb_image.hpp /usr/include/stdio.h
src/DGP/Image.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/DGP/Image.o: /usr/include/libio.h /usr/include/_G_config.h
src/DGP/Image.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/DGP/Image.o: /usr/include/bits/sys_errlist.h src/DGP/stb_image_resize.hpp
src/DGP/Image.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/DGP/Image.o: src/DGP/stb_image_write.hpp
src/DGP/Log.o: src/DGP/Log.hpp src/DGP/Platform.hpp
src/DGP/Log.o: src/DGP/SymbolVisibility.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Log.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/Log.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Log.o: src/DGP/Common.hpp src/DGP/CommonEnums.hpp
src/DGP/Log.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp src/DGP/StringAlg.hpp
src/DGP/Log.o: /usr/include/fnmatch.h
src/DGP/Math.o: src/DGP/Math.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/Math.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/DGP/Math.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/DGP/Math.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/Math.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/Math.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/Math.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/DGP/Math.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/Math.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/Math.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/Math.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/DGP/Math.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Math.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/DGP/Math.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Math.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Math.o: /usr/include/bits/mathcalls.h
src/DGP/MathTables.o: src/DGP/Math.hpp src/DGP/Common.hpp
src/DGP/MathTables.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/MathTables.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/MathTables.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/MathTables.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/MathTables.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/MathTables.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/MathTables.o: /usr/include/fnmatch.h src/DGP/Random.hpp
src/DGP/MathTables.o: /usr/include/math.h /usr/include/features.h
src/DGP/MathTables.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/DGP/MathTables.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/DGP/MathTables.o: /usr/include/bits/math-vector.h
src/DGP/MathTables.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/MathTables.o: /usr/include/bits/huge_val.h
src/DGP/MathTables.o: /usr/include/bits/huge_valf.h
src/DGP/MathTables.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/MathTables.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/MathTables.o: /usr/include/bits/mathcalls.h
src/DGP/Polygon2.o: src/DGP/Polygon2.hpp src/DGP/Common.hpp
src/DGP/Polygon2.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/Polygon2.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Polygon2.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Polygon2.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Polygon2.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Polygon2.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Polygon2.o: /usr/include/fnmatch.h src/DGP/Vector2.hpp
src/DGP/Polygon2.o: src/DGP/VectorN.hpp src/DGP/Math.hpp src/DGP/Random.hpp
src/DGP/Polygon2.o: /usr/include/math.h /usr/include/features.h
src/DGP/Polygon2.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/DGP/Polygon2.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/DGP/Polygon2.o: /usr/include/bits/math-vector.h
src/DGP/Polygon2.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Polygon2.o: /usr/include/bits/huge_val.h
src/DGP/Polygon2.o: /usr/include/bits/huge_valf.h
src/DGP/Polygon2.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Polygon2.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Polygon2.o: /usr/include/bits/mathcalls.h src/DGP/Vector3.hpp
src/DGP/Polygon2.o: src/DGP/Vector4.hpp src/DGP/Polygon3.hpp
src/DGP/Polygon2.o: src/DGP/AxisAlignedBox3.hpp src/DGP/AxisAlignedBoxN.hpp
src/DGP/Polygon2.o: src/DGP/RayIntersectableN.hpp src/DGP/RayN.hpp
src/DGP/Polygon2.o: src/DGP/CoordinateFrameN.hpp src/DGP/RigidTransformN.hpp
src/DGP/Polygon2.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Polygon2.o: src/DGP/AddressableMatrix.hpp
src/DGP/Polygon2.o: src/DGP/IteratableMatrix.hpp src/DGP/BasicMatrix.hpp
src/DGP/Polygon2.o: src/DGP/MatrixInvert.hpp src/DGP/MatrixInvertTmpl.hpp
src/DGP/Polygon2.o: src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp
src/DGP/Polygon2.o: src/DGP/Matrix4.hpp src/DGP/AffineTransform2.hpp
src/DGP/Polygon2.o: src/DGP/AffineTransform3.hpp src/DGP/RigidTransform2.hpp
src/DGP/Polygon2.o: src/DGP/RigidTransform3.hpp src/DGP/CoordinateFrame2.hpp
src/DGP/Polygon2.o: src/DGP/CoordinateFrame3.hpp src/DGP/Ray3.hpp
src/DGP/Polygon2.o: src/DGP/RayIntersectable3.hpp
src/DGP/Polygon2.o: src/DGP/Triangle_triangle.hpp
src/DGP/Polygon3.o: src/DGP/Polygon3.hpp src/DGP/Common.hpp
src/DGP/Polygon3.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/Polygon3.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Polygon3.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Polygon3.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Polygon3.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Polygon3.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Polygon3.o: /usr/include/fnmatch.h src/DGP/AxisAlignedBox3.hpp
src/DGP/Polygon3.o: src/DGP/AxisAlignedBoxN.hpp src/DGP/Math.hpp
src/DGP/Polygon3.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/Polygon3.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/Polygon3.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/Polygon3.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/DGP/Polygon3.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Polygon3.o: /usr/include/bits/huge_val.h
src/DGP/Polygon3.o: /usr/include/bits/huge_valf.h
src/DGP/Polygon3.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Polygon3.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Polygon3.o: /usr/include/bits/mathcalls.h
src/DGP/Polygon3.o: src/DGP/RayIntersectableN.hpp src/DGP/RayN.hpp
src/DGP/Polygon3.o: src/DGP/CoordinateFrameN.hpp src/DGP/RigidTransformN.hpp
src/DGP/Polygon3.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Polygon3.o: src/DGP/AddressableMatrix.hpp
src/DGP/Polygon3.o: src/DGP/IteratableMatrix.hpp src/DGP/BasicMatrix.hpp
src/DGP/Polygon3.o: src/DGP/MatrixInvert.hpp src/DGP/MatrixInvertTmpl.hpp
src/DGP/Polygon3.o: src/DGP/VectorN.hpp src/DGP/Vector2.hpp
src/DGP/Polygon3.o: src/DGP/Vector3.hpp src/DGP/Vector4.hpp
src/DGP/Polygon3.o: src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp
src/DGP/Polygon3.o: src/DGP/Matrix4.hpp src/DGP/AffineTransform2.hpp
src/DGP/Polygon3.o: src/DGP/AffineTransform3.hpp src/DGP/RigidTransform2.hpp
src/DGP/Polygon3.o: src/DGP/RigidTransform3.hpp src/DGP/CoordinateFrame2.hpp
src/DGP/Polygon3.o: src/DGP/CoordinateFrame3.hpp src/DGP/Ray3.hpp
src/DGP/Polygon3.o: src/DGP/RayIntersectable3.hpp
src/DGP/Quat.o: src/DGP/Quat.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/Quat.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/DGP/Quat.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/DGP/Quat.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/Quat.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/Quat.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/Quat.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h src/DGP/Math.hpp
src/DGP/Quat.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/Quat.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/Quat.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/Quat.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/DGP/Quat.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Quat.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/DGP/Quat.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Quat.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Quat.o: /usr/include/bits/mathcalls.h src/DGP/Matrix3.hpp
src/DGP/Quat.o: src/DGP/Matrix2.hpp src/DGP/MatrixMN.hpp
src/DGP/Quat.o: src/DGP/AddressableMatrix.hpp src/DGP/IteratableMatrix.hpp
src/DGP/Quat.o: src/DGP/BasicMatrix.hpp src/DGP/MatrixInvert.hpp
src/DGP/Quat.o: src/DGP/MatrixInvertTmpl.hpp src/DGP/VectorN.hpp
src/DGP/Quat.o: src/DGP/Vector2.hpp src/DGP/Vector3.hpp src/DGP/Vector4.hpp
src/DGP/Quat.o: src/DGP/Matrix4.hpp
src/DGP/Random.o: src/DGP/Random.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/Random.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/DGP/Random.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/DGP/Random.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/Random.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/Random.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/Random.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/DGP/Random.o: src/DGP/Math.hpp /usr/include/math.h
src/DGP/Random.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/Random.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/Random.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/DGP/Random.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Random.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/DGP/Random.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Random.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Random.o: /usr/include/bits/mathcalls.h /usr/include/unistd.h
src/DGP/Random.o: /usr/include/bits/posix_opt.h
src/DGP/Random.o: /usr/include/bits/environments.h /usr/include/bits/types.h
src/DGP/Random.o: /usr/include/bits/typesizes.h /usr/include/bits/confname.h
src/DGP/Random.o: /usr/include/getopt.h
src/DGP/Serializable.o: src/DGP/Serializable.hpp src/DGP/Common.hpp
src/DGP/Serializable.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/Serializable.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Serializable.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Serializable.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Serializable.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Serializable.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Serializable.o: /usr/include/fnmatch.h src/DGP/IOStream.hpp
src/DGP/Serializable.o: src/DGP/BinaryInputStream.hpp src/DGP/Colors.hpp
src/DGP/Serializable.o: src/DGP/ColorL.hpp src/DGP/Math.hpp
src/DGP/Serializable.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/Serializable.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/Serializable.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/Serializable.o: /usr/include/gnu/stubs.h
src/DGP/Serializable.o: /usr/include/bits/math-vector.h
src/DGP/Serializable.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Serializable.o: /usr/include/bits/huge_val.h
src/DGP/Serializable.o: /usr/include/bits/huge_valf.h
src/DGP/Serializable.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Serializable.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Serializable.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/DGP/Serializable.o: src/DGP/ColorRGB.hpp src/DGP/Vector3.hpp
src/DGP/Serializable.o: src/DGP/Vector2.hpp src/DGP/VectorN.hpp
src/DGP/Serializable.o: src/DGP/Vector4.hpp src/DGP/ColorRGB8.hpp
src/DGP/Serializable.o: src/DGP/ColorRGBA.hpp src/DGP/ColorRGBA8.hpp
src/DGP/Serializable.o: src/DGP/CoordinateFrame3.hpp
src/DGP/Serializable.o: src/DGP/CoordinateFrameN.hpp
src/DGP/Serializable.o: src/DGP/RigidTransformN.hpp
src/DGP/Serializable.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Serializable.o: src/DGP/AddressableMatrix.hpp
src/DGP/Serializable.o: src/DGP/IteratableMatrix.hpp src/DGP/BasicMatrix.hpp
src/DGP/Serializable.o: src/DGP/MatrixInvert.hpp src/DGP/MatrixInvertTmpl.hpp
src/DGP/Serializable.o: src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp
src/DGP/Serializable.o: src/DGP/Matrix4.hpp src/DGP/AffineTransform2.hpp
src/DGP/Serializable.o: src/DGP/AffineTransform3.hpp
src/DGP/Serializable.o: src/DGP/RigidTransform2.hpp
src/DGP/Serializable.o: src/DGP/RigidTransform3.hpp
src/DGP/Serializable.o: src/DGP/CoordinateFrame2.hpp src/DGP/NamedObject.hpp
src/DGP/Serializable.o: src/DGP/Plane3.hpp src/DGP/Hyperplane3.hpp
src/DGP/Serializable.o: src/DGP/HyperplaneN.hpp src/DGP/RayIntersectableN.hpp
src/DGP/Serializable.o: src/DGP/RayN.hpp src/DGP/Ray3.hpp
src/DGP/Serializable.o: src/DGP/RayIntersectable3.hpp
src/DGP/Serializable.o: src/DGP/BinaryOutputStream.hpp
src/DGP/Serializable.o: src/DGP/TextInputStream.hpp
src/DGP/Serializable.o: src/DGP/TextOutputStream.hpp
src/DGP/stb_image.o: src/DGP/stb_image.hpp /usr/include/stdio.h
src/DGP/stb_image.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/stb_image.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/stb_image.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
src/DGP/stb_image.o: /usr/include/bits/typesizes.h /usr/include/libio.h
src/DGP/stb_image.o: /usr/include/_G_config.h /usr/include/wchar.h
src/DGP/stb_image.o: /usr/include/bits/stdio_lim.h
src/DGP/stb_image.o: /usr/include/bits/sys_errlist.h
src/DGP/stb_image_resize.o: src/DGP/stb_image_resize.hpp
src/DGP/stb_image_resize.o: /usr/include/stdint.h /usr/include/features.h
src/DGP/stb_image_resize.o: /usr/include/stdc-predef.h
src/DGP/stb_image_resize.o: /usr/include/sys/cdefs.h
src/DGP/stb_image_resize.o: /usr/include/bits/wordsize.h
src/DGP/stb_image_resize.o: /usr/include/gnu/stubs.h
src/DGP/stb_image_resize.o: /usr/include/bits/wchar.h
src/DGP/stb_image_write.o: src/DGP/stb_image_write.hpp
src/DGP/Stopwatch.o: src/DGP/Stopwatch.hpp src/DGP/Common.hpp
src/DGP/Stopwatch.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/Stopwatch.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Stopwatch.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Stopwatch.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Stopwatch.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Stopwatch.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Stopwatch.o: /usr/include/fnmatch.h src/DGP/System.hpp
src/DGP/Stopwatch.o: /usr/include/sys/time.h /usr/include/features.h
src/DGP/Stopwatch.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/DGP/Stopwatch.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/DGP/Stopwatch.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/DGP/Stopwatch.o: /usr/include/time.h /usr/include/bits/time.h
src/DGP/Stopwatch.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/DGP/Stopwatch.o: /usr/include/bits/sigset.h src/DGP/Math.hpp
src/DGP/Stopwatch.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/Stopwatch.o: /usr/include/bits/math-vector.h
src/DGP/Stopwatch.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Stopwatch.o: /usr/include/bits/huge_val.h
src/DGP/Stopwatch.o: /usr/include/bits/huge_valf.h
src/DGP/Stopwatch.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Stopwatch.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Stopwatch.o: /usr/include/bits/mathcalls.h
src/DGP/StringAlg.o: src/DGP/StringAlg.hpp src/DGP/Common.hpp
src/DGP/StringAlg.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/StringAlg.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/StringAlg.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/StringAlg.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/StringAlg.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/StringAlg.o: src/DGP/Spinlock.hpp /usr/include/fnmatch.h
src/DGP/SVD.o: src/DGP/SVD.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/SVD.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/DGP/SVD.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/DGP/SVD.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/SVD.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/SVD.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/SVD.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/DGP/SVD.o: src/DGP/AddressableMatrix.hpp src/DGP/IteratableMatrix.hpp
src/DGP/SVD.o: src/DGP/BasicMatrix.hpp src/DGP/Matrix.hpp
src/DGP/SVD.o: src/DGP/FastCopy.hpp src/DGP/MatrixInvert.hpp
src/DGP/SVD.o: src/DGP/MatrixInvertTmpl.hpp src/DGP/ResizableMatrix.hpp
src/DGP/SVD.o: src/DGP/TransposedMatrix.hpp src/DGP/Math.hpp
src/DGP/SVD.o: src/DGP/Random.hpp /usr/include/math.h /usr/include/features.h
src/DGP/SVD.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/DGP/SVD.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/DGP/SVD.o: /usr/include/bits/math-vector.h
src/DGP/SVD.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/SVD.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/DGP/SVD.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/SVD.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/SVD.o: /usr/include/bits/mathcalls.h
src/DGP/System.o: src/DGP/System.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/System.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/DGP/System.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/DGP/System.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/System.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/System.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/System.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/DGP/System.o: /usr/include/sys/time.h /usr/include/features.h
src/DGP/System.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/DGP/System.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/DGP/System.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/DGP/System.o: /usr/include/time.h /usr/include/bits/time.h
src/DGP/System.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/DGP/System.o: /usr/include/bits/sigset.h /usr/include/unistd.h
src/DGP/System.o: /usr/include/bits/posix_opt.h
src/DGP/System.o: /usr/include/bits/environments.h
src/DGP/System.o: /usr/include/bits/confname.h /usr/include/getopt.h
src/DGP/TextInputStream.o: src/DGP/TextInputStream.hpp src/DGP/Common.hpp
src/DGP/TextInputStream.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/TextInputStream.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/TextInputStream.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/TextInputStream.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/TextInputStream.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/TextInputStream.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/TextInputStream.o: /usr/include/fnmatch.h src/DGP/NamedObject.hpp
src/DGP/TextInputStream.o: src/DGP/FilePath.hpp src/DGP/FileSystem.hpp
src/DGP/TextInputStream.o: src/DGP/Math.hpp src/DGP/Random.hpp
src/DGP/TextInputStream.o: /usr/include/math.h /usr/include/features.h
src/DGP/TextInputStream.o: /usr/include/stdc-predef.h
src/DGP/TextInputStream.o: /usr/include/sys/cdefs.h
src/DGP/TextInputStream.o: /usr/include/bits/wordsize.h
src/DGP/TextInputStream.o: /usr/include/gnu/stubs.h
src/DGP/TextInputStream.o: /usr/include/bits/math-vector.h
src/DGP/TextInputStream.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/TextInputStream.o: /usr/include/bits/huge_val.h
src/DGP/TextInputStream.o: /usr/include/bits/huge_valf.h
src/DGP/TextInputStream.o: /usr/include/bits/huge_vall.h
src/DGP/TextInputStream.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
src/DGP/TextInputStream.o: /usr/include/bits/mathdef.h
src/DGP/TextInputStream.o: /usr/include/bits/mathcalls.h
src/DGP/TextOutputStream.o: src/DGP/TextOutputStream.hpp src/DGP/Common.hpp
src/DGP/TextOutputStream.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/TextOutputStream.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/TextOutputStream.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/TextOutputStream.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/TextOutputStream.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/TextOutputStream.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/TextOutputStream.o: /usr/include/fnmatch.h src/DGP/NamedObject.hpp
src/DGP/TextOutputStream.o: src/DGP/FilePath.hpp src/DGP/FileSystem.hpp
src/DGP/TextOutputStream.o: src/DGP/Math.hpp src/DGP/Random.hpp
src/DGP/TextOutputStream.o: /usr/include/math.h /usr/include/features.h
src/DGP/TextOutputStream.o: /usr/include/stdc-predef.h
src/DGP/TextOutputStream.o: /usr/include/sys/cdefs.h
src/DGP/TextOutputStream.o: /usr/include/bits/wordsize.h
src/DGP/TextOutputStream.o: /usr/include/gnu/stubs.h
src/DGP/TextOutputStream.o: /usr/include/bits/math-vector.h
src/DGP/TextOutputStream.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/TextOutputStream.o: /usr/include/bits/huge_val.h
src/DGP/TextOutputStream.o: /usr/include/bits/huge_valf.h
src/DGP/TextOutputStream.o: /usr/include/bits/huge_vall.h
src/DGP/TextOutputStream.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
src/DGP/TextOutputStream.o: /usr/include/bits/mathdef.h
src/DGP/TextOutputStream.o: /usr/include/bits/mathcalls.h
src/DGP/TextOutputStream.o: /usr/include/stdio.h /usr/include/bits/types.h
src/DGP/TextOutputStream.o: /usr/include/bits/typesizes.h
src/DGP/TextOutputStream.o: /usr/include/libio.h /usr/include/_G_config.h
src/DGP/TextOutputStream.o: /usr/include/wchar.h
src/DGP/TextOutputStream.o: /usr/include/bits/stdio_lim.h
src/DGP/TextOutputStream.o: /usr/include/bits/sys_errlist.h
src/DGP/Triangle3.o: src/DGP/Triangle3.hpp src/DGP/Common.hpp
src/DGP/Triangle3.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/Triangle3.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Triangle3.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Triangle3.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Triangle3.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Triangle3.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Triangle3.o: /usr/include/fnmatch.h src/DGP/AxisAlignedBox3.hpp
src/DGP/Triangle3.o: src/DGP/AxisAlignedBoxN.hpp src/DGP/Math.hpp
src/DGP/Triangle3.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/Triangle3.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/Triangle3.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/Triangle3.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/DGP/Triangle3.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Triangle3.o: /usr/include/bits/huge_val.h
src/DGP/Triangle3.o: /usr/include/bits/huge_valf.h
src/DGP/Triangle3.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Triangle3.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Triangle3.o: /usr/include/bits/mathcalls.h
src/DGP/Triangle3.o: src/DGP/RayIntersectableN.hpp src/DGP/RayN.hpp
src/DGP/Triangle3.o: src/DGP/CoordinateFrameN.hpp src/DGP/RigidTransformN.hpp
src/DGP/Triangle3.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Triangle3.o: src/DGP/AddressableMatrix.hpp
src/DGP/Triangle3.o: src/DGP/IteratableMatrix.hpp src/DGP/BasicMatrix.hpp
src/DGP/Triangle3.o: src/DGP/MatrixInvert.hpp src/DGP/MatrixInvertTmpl.hpp
src/DGP/Triangle3.o: src/DGP/VectorN.hpp src/DGP/Vector2.hpp
src/DGP/Triangle3.o: src/DGP/Vector3.hpp src/DGP/Vector4.hpp
src/DGP/Triangle3.o: src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp
src/DGP/Triangle3.o: src/DGP/Matrix4.hpp src/DGP/AffineTransform2.hpp
src/DGP/Triangle3.o: src/DGP/AffineTransform3.hpp src/DGP/RigidTransform2.hpp
src/DGP/Triangle3.o: src/DGP/RigidTransform3.hpp src/DGP/CoordinateFrame2.hpp
src/DGP/Triangle3.o: src/DGP/CoordinateFrame3.hpp src/DGP/Ray3.hpp
src/DGP/Triangle3.o: src/DGP/RayIntersectable3.hpp src/DGP/Ball3.hpp
src/DGP/Triangle3.o: src/DGP/BallN.hpp src/DGP/Box3.hpp src/DGP/BoxN.hpp
src/DGP/Triangle3.o: src/DGP/LineSegment3.hpp src/DGP/LineSegmentN.hpp
src/DGP/Triangle3.o: src/DGP/LineSegment2.hpp src/DGP/Plane3.hpp
src/DGP/Triangle3.o: src/DGP/Hyperplane3.hpp src/DGP/HyperplaneN.hpp
src/DGP/Triangle_triangle.o: /usr/include/stdio.h /usr/include/features.h
src/DGP/Triangle_triangle.o: /usr/include/stdc-predef.h
src/DGP/Triangle_triangle.o: /usr/include/sys/cdefs.h
src/DGP/Triangle_triangle.o: /usr/include/bits/wordsize.h
src/DGP/Triangle_triangle.o: /usr/include/gnu/stubs.h
src/DGP/Triangle_triangle.o: /usr/include/bits/types.h
src/DGP/Triangle_triangle.o: /usr/include/bits/typesizes.h
src/DGP/Triangle_triangle.o: /usr/include/libio.h /usr/include/_G_config.h
src/DGP/Triangle_triangle.o: /usr/include/wchar.h
src/DGP/Triangle_triangle.o: /usr/include/bits/stdio_lim.h
src/DGP/Triangle_triangle.o: /usr/include/bits/sys_errlist.h
src/DGP/Triangle_triangle.o: /usr/include/stdlib.h
src/DGP/Triangle_triangle.o: /usr/include/bits/waitflags.h
src/DGP/Triangle_triangle.o: /usr/include/bits/waitstatus.h
src/DGP/Triangle_triangle.o: /usr/include/endian.h /usr/include/bits/endian.h
src/DGP/Triangle_triangle.o: /usr/include/bits/byteswap.h
src/DGP/Triangle_triangle.o: /usr/include/bits/byteswap-16.h
src/DGP/Triangle_triangle.o: /usr/include/sys/types.h /usr/include/time.h
src/DGP/Triangle_triangle.o: /usr/include/sys/select.h
src/DGP/Triangle_triangle.o: /usr/include/bits/select.h
src/DGP/Triangle_triangle.o: /usr/include/bits/sigset.h
src/DGP/Triangle_triangle.o: /usr/include/bits/time.h
src/DGP/Triangle_triangle.o: /usr/include/sys/sysmacros.h
src/DGP/Triangle_triangle.o: /usr/include/bits/pthreadtypes.h
src/DGP/Triangle_triangle.o: /usr/include/alloca.h
src/DGP/Triangle_triangle.o: /usr/include/bits/stdlib-float.h
src/DGP/Triangle_triangle.o: /usr/include/string.h /usr/include/xlocale.h
src/DGP/Triangle_triangle.o: /usr/include/math.h
src/DGP/Triangle_triangle.o: /usr/include/bits/math-vector.h
src/DGP/Triangle_triangle.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Triangle_triangle.o: /usr/include/bits/huge_val.h
src/DGP/Triangle_triangle.o: /usr/include/bits/huge_valf.h
src/DGP/Triangle_triangle.o: /usr/include/bits/huge_vall.h
src/DGP/Triangle_triangle.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
src/DGP/Triangle_triangle.o: /usr/include/bits/mathdef.h
src/DGP/Triangle_triangle.o: /usr/include/bits/mathcalls.h
src/DGP/Triangle_triangle.o: src/DGP/Triangle_triangle.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Graphics/Framebuffer.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/SymbolVisibility.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/AtomicInt32.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/NumericTypes.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Common.hpp /usr/include/fnmatch.h
src/DGP/Graphics/Framebuffer.o: src/DGP/NamedObject.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Graphics/GLHeaders.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/FilePath.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Graphics/glew.hpp
src/DGP/Graphics/Framebuffer.o: /usr/include/stdint.h /usr/include/features.h
src/DGP/Graphics/Framebuffer.o: /usr/include/stdc-predef.h
src/DGP/Graphics/Framebuffer.o: /usr/include/sys/cdefs.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/wordsize.h
src/DGP/Graphics/Framebuffer.o: /usr/include/gnu/stubs.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/wchar.h
src/DGP/Graphics/Framebuffer.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
src/DGP/Graphics/Framebuffer.o: src/DGP/Graphics/Texture.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Image.hpp src/DGP/IOStream.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/BinaryInputStream.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Colors.hpp src/DGP/ColorL.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Math.hpp src/DGP/Random.hpp
src/DGP/Graphics/Framebuffer.o: /usr/include/math.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/math-vector.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/huge_val.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/huge_valf.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/huge_vall.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/inf.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/nan.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/mathdef.h
src/DGP/Graphics/Framebuffer.o: /usr/include/bits/mathcalls.h
src/DGP/Graphics/Framebuffer.o: src/DGP/ColorL8.hpp src/DGP/ColorRGB.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Vector3.hpp src/DGP/Vector2.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/VectorN.hpp src/DGP/Vector4.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/ColorRGB8.hpp src/DGP/ColorRGBA.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/ColorRGBA8.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/CoordinateFrame3.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/CoordinateFrameN.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/RigidTransformN.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/AffineTransformN.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/MatrixMN.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/AddressableMatrix.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/IteratableMatrix.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/BasicMatrix.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/MatrixInvert.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/MatrixInvertTmpl.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Matrix4.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/AffineTransform2.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/AffineTransform3.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/RigidTransform2.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/RigidTransform3.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/CoordinateFrame2.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/NamedObject.hpp src/DGP/Plane3.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Hyperplane3.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/HyperplaneN.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/RayIntersectableN.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/RayN.hpp src/DGP/Ray3.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/RayIntersectable3.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/BinaryOutputStream.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/TextInputStream.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/TextOutputStream.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Serializable.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Graphics/TextureFormat.hpp
src/DGP/Graphics/Framebuffer.o: src/DGP/Graphics/GLCaps.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Graphics/GLCaps.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Graphics/Texture.hpp src/DGP/Common.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Common.hpp /usr/include/fnmatch.h
src/DGP/Graphics/GLCaps.o: src/DGP/NamedObject.hpp src/DGP/Image.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/IOStream.hpp src/DGP/BinaryInputStream.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Colors.hpp src/DGP/ColorL.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Math.hpp src/DGP/Random.hpp
src/DGP/Graphics/GLCaps.o: /usr/include/math.h /usr/include/features.h
src/DGP/Graphics/GLCaps.o: /usr/include/stdc-predef.h
src/DGP/Graphics/GLCaps.o: /usr/include/sys/cdefs.h
src/DGP/Graphics/GLCaps.o: /usr/include/bits/wordsize.h
src/DGP/Graphics/GLCaps.o: /usr/include/gnu/stubs.h
src/DGP/Graphics/GLCaps.o: /usr/include/bits/math-vector.h
src/DGP/Graphics/GLCaps.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Graphics/GLCaps.o: /usr/include/bits/huge_val.h
src/DGP/Graphics/GLCaps.o: /usr/include/bits/huge_valf.h
src/DGP/Graphics/GLCaps.o: /usr/include/bits/huge_vall.h
src/DGP/Graphics/GLCaps.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
src/DGP/Graphics/GLCaps.o: /usr/include/bits/mathdef.h
src/DGP/Graphics/GLCaps.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/ColorRGB.hpp src/DGP/Vector3.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Vector2.hpp src/DGP/VectorN.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Vector4.hpp src/DGP/ColorRGB8.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/ColorRGBA.hpp src/DGP/ColorRGBA8.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/CoordinateFrame3.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/CoordinateFrameN.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/RigidTransformN.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/AddressableMatrix.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/IteratableMatrix.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/BasicMatrix.hpp src/DGP/MatrixInvert.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/MatrixInvertTmpl.hpp src/DGP/Matrix2.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Matrix3.hpp src/DGP/Matrix4.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/AffineTransform2.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/AffineTransform3.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/RigidTransform2.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/RigidTransform3.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/CoordinateFrame2.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/NamedObject.hpp src/DGP/Plane3.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Hyperplane3.hpp src/DGP/HyperplaneN.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/RayIntersectableN.hpp src/DGP/RayN.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Ray3.hpp src/DGP/RayIntersectable3.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/BinaryOutputStream.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/TextInputStream.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/TextOutputStream.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Serializable.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Graphics/GLHeaders.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/FilePath.hpp src/DGP/Graphics/glew.hpp
src/DGP/Graphics/GLCaps.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/DGP/Graphics/GLCaps.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
src/DGP/Graphics/GLCaps.o: src/DGP/Graphics/TextureFormat.hpp
src/DGP/Graphics/GLCaps.o: src/DGP/Math.hpp
src/DGP/Graphics/glew.o: src/DGP/Graphics/glew.hpp /usr/include/stdint.h
src/DGP/Graphics/glew.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/Graphics/glew.o: /usr/include/sys/cdefs.h
src/DGP/Graphics/glew.o: /usr/include/bits/wordsize.h
src/DGP/Graphics/glew.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
src/DGP/Graphics/glew.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
src/DGP/Graphics/glew.o: src/DGP/Graphics/glxew.hpp /usr/include/X11/Xlib.h
src/DGP/Graphics/glew.o: /usr/include/sys/types.h /usr/include/bits/types.h
src/DGP/Graphics/glew.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/DGP/Graphics/glew.o: /usr/include/endian.h /usr/include/bits/endian.h
src/DGP/Graphics/glew.o: /usr/include/bits/byteswap.h
src/DGP/Graphics/glew.o: /usr/include/bits/byteswap-16.h
src/DGP/Graphics/glew.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/DGP/Graphics/glew.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/DGP/Graphics/glew.o: /usr/include/sys/sysmacros.h
src/DGP/Graphics/glew.o: /usr/include/bits/pthreadtypes.h
src/DGP/Graphics/glew.o: /usr/include/X11/X.h /usr/include/X11/Xfuncproto.h
src/DGP/Graphics/glew.o: /usr/include/X11/Xosdefs.h /usr/include/X11/Xutil.h
src/DGP/Graphics/glew.o: /usr/include/X11/keysym.h
src/DGP/Graphics/glew.o: /usr/include/X11/keysymdef.h /usr/include/X11/Xmd.h
src/DGP/Graphics/RenderSystem.o: src/DGP/Graphics/RenderSystem.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/SymbolVisibility.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/AtomicInt32.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/NumericTypes.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/CommonEnums.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/StringAlg.hpp src/DGP/Common.hpp
src/DGP/Graphics/RenderSystem.o: /usr/include/fnmatch.h src/DGP/Camera.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Serializable.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/IOStream.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/BinaryInputStream.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Colors.hpp src/DGP/ColorL.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Math.hpp src/DGP/Random.hpp
src/DGP/Graphics/RenderSystem.o: /usr/include/math.h /usr/include/features.h
src/DGP/Graphics/RenderSystem.o: /usr/include/stdc-predef.h
src/DGP/Graphics/RenderSystem.o: /usr/include/sys/cdefs.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/wordsize.h
src/DGP/Graphics/RenderSystem.o: /usr/include/gnu/stubs.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/math-vector.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/huge_val.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/huge_valf.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/huge_vall.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/inf.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/nan.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/mathdef.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/mathcalls.h
src/DGP/Graphics/RenderSystem.o: src/DGP/ColorL8.hpp src/DGP/ColorRGB.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Vector3.hpp src/DGP/Vector2.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/VectorN.hpp src/DGP/Vector4.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/ColorRGB8.hpp src/DGP/ColorRGBA.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/ColorRGBA8.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/CoordinateFrame3.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/CoordinateFrameN.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/RigidTransformN.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/AffineTransformN.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/MatrixMN.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/AddressableMatrix.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/IteratableMatrix.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/BasicMatrix.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/MatrixInvert.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/MatrixInvertTmpl.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Matrix4.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/AffineTransform2.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/AffineTransform3.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/RigidTransform2.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/RigidTransform3.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/CoordinateFrame2.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/NamedObject.hpp src/DGP/Plane3.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Hyperplane3.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/HyperplaneN.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/RayIntersectableN.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/RayN.hpp src/DGP/Ray3.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/RayIntersectable3.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/BinaryOutputStream.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/TextInputStream.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/TextOutputStream.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Colors.hpp src/DGP/Image.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/NamedObject.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Graphics/Framebuffer.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Graphics/GLHeaders.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/FilePath.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Graphics/glew.hpp
src/DGP/Graphics/RenderSystem.o: /usr/include/stdint.h
src/DGP/Graphics/RenderSystem.o: /usr/include/bits/wchar.h
src/DGP/Graphics/RenderSystem.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
src/DGP/Graphics/RenderSystem.o: src/DGP/Graphics/Texture.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Graphics/TextureFormat.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Graphics/Shader.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/MatrixMN.hpp src/DGP/VectorN.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Graphics/VAR.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Graphics/VARArea.hpp
src/DGP/Graphics/RenderSystem.o: src/DGP/Graphics/GLCaps.hpp
src/DGP/Graphics/Shader.o: src/DGP/Graphics/Shader.hpp src/DGP/Common.hpp
src/DGP/Graphics/Shader.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/Graphics/Shader.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Graphics/Shader.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Graphics/Shader.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Graphics/Shader.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Graphics/Shader.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Graphics/Shader.o: src/DGP/Common.hpp /usr/include/fnmatch.h
src/DGP/Graphics/Shader.o: src/DGP/Colors.hpp src/DGP/MatrixMN.hpp
src/DGP/Graphics/Shader.o: src/DGP/VectorN.hpp src/DGP/NamedObject.hpp
src/DGP/Graphics/Shader.o: src/DGP/Graphics/Texture.hpp src/DGP/Image.hpp
src/DGP/Graphics/Shader.o: src/DGP/IOStream.hpp src/DGP/BinaryInputStream.hpp
src/DGP/Graphics/Shader.o: src/DGP/Colors.hpp src/DGP/ColorL.hpp
src/DGP/Graphics/Shader.o: src/DGP/Math.hpp src/DGP/Random.hpp
src/DGP/Graphics/Shader.o: /usr/include/math.h /usr/include/features.h
src/DGP/Graphics/Shader.o: /usr/include/stdc-predef.h
src/DGP/Graphics/Shader.o: /usr/include/sys/cdefs.h
src/DGP/Graphics/Shader.o: /usr/include/bits/wordsize.h
src/DGP/Graphics/Shader.o: /usr/include/gnu/stubs.h
src/DGP/Graphics/Shader.o: /usr/include/bits/math-vector.h
src/DGP/Graphics/Shader.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Graphics/Shader.o: /usr/include/bits/huge_val.h
src/DGP/Graphics/Shader.o: /usr/include/bits/huge_valf.h
src/DGP/Graphics/Shader.o: /usr/include/bits/huge_vall.h
src/DGP/Graphics/Shader.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
src/DGP/Graphics/Shader.o: /usr/include/bits/mathdef.h
src/DGP/Graphics/Shader.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/DGP/Graphics/Shader.o: src/DGP/ColorRGB.hpp src/DGP/Vector3.hpp
src/DGP/Graphics/Shader.o: src/DGP/Vector2.hpp src/DGP/VectorN.hpp
src/DGP/Graphics/Shader.o: src/DGP/Vector4.hpp src/DGP/ColorRGB8.hpp
src/DGP/Graphics/Shader.o: src/DGP/ColorRGBA.hpp src/DGP/ColorRGBA8.hpp
src/DGP/Graphics/Shader.o: src/DGP/CoordinateFrame3.hpp
src/DGP/Graphics/Shader.o: src/DGP/CoordinateFrameN.hpp
src/DGP/Graphics/Shader.o: src/DGP/RigidTransformN.hpp
src/DGP/Graphics/Shader.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Graphics/Shader.o: src/DGP/AddressableMatrix.hpp
src/DGP/Graphics/Shader.o: src/DGP/IteratableMatrix.hpp
src/DGP/Graphics/Shader.o: src/DGP/BasicMatrix.hpp src/DGP/MatrixInvert.hpp
src/DGP/Graphics/Shader.o: src/DGP/MatrixInvertTmpl.hpp src/DGP/Matrix2.hpp
src/DGP/Graphics/Shader.o: src/DGP/Matrix3.hpp src/DGP/Matrix4.hpp
src/DGP/Graphics/Shader.o: src/DGP/AffineTransform2.hpp
src/DGP/Graphics/Shader.o: src/DGP/AffineTransform3.hpp
src/DGP/Graphics/Shader.o: src/DGP/RigidTransform2.hpp
src/DGP/Graphics/Shader.o: src/DGP/RigidTransform3.hpp
src/DGP/Graphics/Shader.o: src/DGP/CoordinateFrame2.hpp
src/DGP/Graphics/Shader.o: src/DGP/NamedObject.hpp src/DGP/Plane3.hpp
src/DGP/Graphics/Shader.o: src/DGP/Hyperplane3.hpp src/DGP/HyperplaneN.hpp
src/DGP/Graphics/Shader.o: src/DGP/RayIntersectableN.hpp src/DGP/RayN.hpp
src/DGP/Graphics/Shader.o: src/DGP/Ray3.hpp src/DGP/RayIntersectable3.hpp
src/DGP/Graphics/Shader.o: src/DGP/BinaryOutputStream.hpp
src/DGP/Graphics/Shader.o: src/DGP/TextInputStream.hpp
src/DGP/Graphics/Shader.o: src/DGP/TextOutputStream.hpp
src/DGP/Graphics/Shader.o: src/DGP/Serializable.hpp
src/DGP/Graphics/Shader.o: src/DGP/Graphics/GLHeaders.hpp
src/DGP/Graphics/Shader.o: src/DGP/FilePath.hpp src/DGP/Graphics/glew.hpp
src/DGP/Graphics/Shader.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/DGP/Graphics/Shader.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
src/DGP/Graphics/Shader.o: src/DGP/Graphics/TextureFormat.hpp
src/DGP/Graphics/Shader.o: src/DGP/FileSystem.hpp src/DGP/Graphics/GLCaps.hpp
src/DGP/Graphics/Texture.o: src/DGP/Graphics/Texture.hpp src/DGP/Common.hpp
src/DGP/Graphics/Texture.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/Graphics/Texture.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Graphics/Texture.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Graphics/Texture.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Graphics/Texture.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Graphics/Texture.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Graphics/Texture.o: src/DGP/Common.hpp /usr/include/fnmatch.h
src/DGP/Graphics/Texture.o: src/DGP/NamedObject.hpp src/DGP/Image.hpp
src/DGP/Graphics/Texture.o: src/DGP/IOStream.hpp
src/DGP/Graphics/Texture.o: src/DGP/BinaryInputStream.hpp src/DGP/Colors.hpp
src/DGP/Graphics/Texture.o: src/DGP/ColorL.hpp src/DGP/Math.hpp
src/DGP/Graphics/Texture.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/Graphics/Texture.o: /usr/include/features.h
src/DGP/Graphics/Texture.o: /usr/include/stdc-predef.h
src/DGP/Graphics/Texture.o: /usr/include/sys/cdefs.h
src/DGP/Graphics/Texture.o: /usr/include/bits/wordsize.h
src/DGP/Graphics/Texture.o: /usr/include/gnu/stubs.h
src/DGP/Graphics/Texture.o: /usr/include/bits/math-vector.h
src/DGP/Graphics/Texture.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Graphics/Texture.o: /usr/include/bits/huge_val.h
src/DGP/Graphics/Texture.o: /usr/include/bits/huge_valf.h
src/DGP/Graphics/Texture.o: /usr/include/bits/huge_vall.h
src/DGP/Graphics/Texture.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
src/DGP/Graphics/Texture.o: /usr/include/bits/mathdef.h
src/DGP/Graphics/Texture.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/DGP/Graphics/Texture.o: src/DGP/ColorRGB.hpp src/DGP/Vector3.hpp
src/DGP/Graphics/Texture.o: src/DGP/Vector2.hpp src/DGP/VectorN.hpp
src/DGP/Graphics/Texture.o: src/DGP/Vector4.hpp src/DGP/ColorRGB8.hpp
src/DGP/Graphics/Texture.o: src/DGP/ColorRGBA.hpp src/DGP/ColorRGBA8.hpp
src/DGP/Graphics/Texture.o: src/DGP/CoordinateFrame3.hpp
src/DGP/Graphics/Texture.o: src/DGP/CoordinateFrameN.hpp
src/DGP/Graphics/Texture.o: src/DGP/RigidTransformN.hpp
src/DGP/Graphics/Texture.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Graphics/Texture.o: src/DGP/AddressableMatrix.hpp
src/DGP/Graphics/Texture.o: src/DGP/IteratableMatrix.hpp
src/DGP/Graphics/Texture.o: src/DGP/BasicMatrix.hpp src/DGP/MatrixInvert.hpp
src/DGP/Graphics/Texture.o: src/DGP/MatrixInvertTmpl.hpp src/DGP/Matrix2.hpp
src/DGP/Graphics/Texture.o: src/DGP/Matrix3.hpp src/DGP/Matrix4.hpp
src/DGP/Graphics/Texture.o: src/DGP/AffineTransform2.hpp
src/DGP/Graphics/Texture.o: src/DGP/AffineTransform3.hpp
src/DGP/Graphics/Texture.o: src/DGP/RigidTransform2.hpp
src/DGP/Graphics/Texture.o: src/DGP/RigidTransform3.hpp
src/DGP/Graphics/Texture.o: src/DGP/CoordinateFrame2.hpp
src/DGP/Graphics/Texture.o: src/DGP/NamedObject.hpp src/DGP/Plane3.hpp
src/DGP/Graphics/Texture.o: src/DGP/Hyperplane3.hpp src/DGP/HyperplaneN.hpp
src/DGP/Graphics/Texture.o: src/DGP/RayIntersectableN.hpp src/DGP/RayN.hpp
src/DGP/Graphics/Texture.o: src/DGP/Ray3.hpp src/DGP/RayIntersectable3.hpp
src/DGP/Graphics/Texture.o: src/DGP/BinaryOutputStream.hpp
src/DGP/Graphics/Texture.o: src/DGP/TextInputStream.hpp
src/DGP/Graphics/Texture.o: src/DGP/TextOutputStream.hpp
src/DGP/Graphics/Texture.o: src/DGP/Serializable.hpp
src/DGP/Graphics/Texture.o: src/DGP/Graphics/GLHeaders.hpp
src/DGP/Graphics/Texture.o: src/DGP/FilePath.hpp src/DGP/Graphics/glew.hpp
src/DGP/Graphics/Texture.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/DGP/Graphics/Texture.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
src/DGP/Graphics/Texture.o: src/DGP/Graphics/TextureFormat.hpp
src/DGP/Graphics/Texture.o: src/DGP/Math.hpp src/DGP/Graphics/GLCaps.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/Graphics/TextureFormat.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/Common.hpp src/DGP/Platform.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/SymbolVisibility.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/AtomicInt32.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/NumericTypes.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/CommonEnums.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/Noncopyable.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Graphics/TextureFormat.o: src/DGP/Common.hpp /usr/include/fnmatch.h
src/DGP/Graphics/TextureFormat.o: src/DGP/Graphics/glew.hpp
src/DGP/Graphics/TextureFormat.o: /usr/include/stdint.h
src/DGP/Graphics/TextureFormat.o: /usr/include/features.h
src/DGP/Graphics/TextureFormat.o: /usr/include/stdc-predef.h
src/DGP/Graphics/TextureFormat.o: /usr/include/sys/cdefs.h
src/DGP/Graphics/TextureFormat.o: /usr/include/bits/wordsize.h
src/DGP/Graphics/TextureFormat.o: /usr/include/gnu/stubs.h
src/DGP/Graphics/TextureFormat.o: /usr/include/bits/wchar.h
src/DGP/Graphics/TextureFormat.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
src/DGP/Graphics/VARArea.o: src/DGP/Graphics/VARArea.hpp src/DGP/Common.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/Graphics/VARArea.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Graphics/VARArea.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Common.hpp /usr/include/fnmatch.h
src/DGP/Graphics/VARArea.o: src/DGP/NamedObject.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Graphics/GLHeaders.hpp
src/DGP/Graphics/VARArea.o: src/DGP/FilePath.hpp src/DGP/Graphics/glew.hpp
src/DGP/Graphics/VARArea.o: /usr/include/stdint.h /usr/include/features.h
src/DGP/Graphics/VARArea.o: /usr/include/stdc-predef.h
src/DGP/Graphics/VARArea.o: /usr/include/sys/cdefs.h
src/DGP/Graphics/VARArea.o: /usr/include/bits/wordsize.h
src/DGP/Graphics/VARArea.o: /usr/include/gnu/stubs.h
src/DGP/Graphics/VARArea.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
src/DGP/Graphics/VARArea.o: /usr/include/GL/gl.h src/DGP/Graphics/GLCaps.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Graphics/Texture.hpp src/DGP/Image.hpp
src/DGP/Graphics/VARArea.o: src/DGP/IOStream.hpp
src/DGP/Graphics/VARArea.o: src/DGP/BinaryInputStream.hpp src/DGP/Colors.hpp
src/DGP/Graphics/VARArea.o: src/DGP/ColorL.hpp src/DGP/Math.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Random.hpp /usr/include/math.h
src/DGP/Graphics/VARArea.o: /usr/include/bits/math-vector.h
src/DGP/Graphics/VARArea.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Graphics/VARArea.o: /usr/include/bits/huge_val.h
src/DGP/Graphics/VARArea.o: /usr/include/bits/huge_valf.h
src/DGP/Graphics/VARArea.o: /usr/include/bits/huge_vall.h
src/DGP/Graphics/VARArea.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
src/DGP/Graphics/VARArea.o: /usr/include/bits/mathdef.h
src/DGP/Graphics/VARArea.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/DGP/Graphics/VARArea.o: src/DGP/ColorRGB.hpp src/DGP/Vector3.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Vector2.hpp src/DGP/VectorN.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Vector4.hpp src/DGP/ColorRGB8.hpp
src/DGP/Graphics/VARArea.o: src/DGP/ColorRGBA.hpp src/DGP/ColorRGBA8.hpp
src/DGP/Graphics/VARArea.o: src/DGP/CoordinateFrame3.hpp
src/DGP/Graphics/VARArea.o: src/DGP/CoordinateFrameN.hpp
src/DGP/Graphics/VARArea.o: src/DGP/RigidTransformN.hpp
src/DGP/Graphics/VARArea.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Graphics/VARArea.o: src/DGP/AddressableMatrix.hpp
src/DGP/Graphics/VARArea.o: src/DGP/IteratableMatrix.hpp
src/DGP/Graphics/VARArea.o: src/DGP/BasicMatrix.hpp src/DGP/MatrixInvert.hpp
src/DGP/Graphics/VARArea.o: src/DGP/MatrixInvertTmpl.hpp src/DGP/Matrix2.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Matrix3.hpp src/DGP/Matrix4.hpp
src/DGP/Graphics/VARArea.o: src/DGP/AffineTransform2.hpp
src/DGP/Graphics/VARArea.o: src/DGP/AffineTransform3.hpp
src/DGP/Graphics/VARArea.o: src/DGP/RigidTransform2.hpp
src/DGP/Graphics/VARArea.o: src/DGP/RigidTransform3.hpp
src/DGP/Graphics/VARArea.o: src/DGP/CoordinateFrame2.hpp
src/DGP/Graphics/VARArea.o: src/DGP/NamedObject.hpp src/DGP/Plane3.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Hyperplane3.hpp src/DGP/HyperplaneN.hpp
src/DGP/Graphics/VARArea.o: src/DGP/RayIntersectableN.hpp src/DGP/RayN.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Ray3.hpp src/DGP/RayIntersectable3.hpp
src/DGP/Graphics/VARArea.o: src/DGP/BinaryOutputStream.hpp
src/DGP/Graphics/VARArea.o: src/DGP/TextInputStream.hpp
src/DGP/Graphics/VARArea.o: src/DGP/TextOutputStream.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Serializable.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Graphics/TextureFormat.hpp
src/DGP/Graphics/VARArea.o: src/DGP/Graphics/VAR.hpp src/DGP/Colors.hpp
src/DGP/Graphics/VARArea.o: src/DGP/VectorN.hpp
src/DGP/Graphics/VAR.o: src/DGP/Graphics/VAR.hpp src/DGP/Common.hpp
src/DGP/Graphics/VAR.o: src/DGP/Platform.hpp src/DGP/SymbolVisibility.hpp
src/DGP/Graphics/VAR.o: src/DGP/AtomicInt32.hpp src/DGP/NumericTypes.hpp
src/DGP/Graphics/VAR.o: src/DGP/CommonEnums.hpp src/DGP/EnumClass.hpp
src/DGP/Graphics/VAR.o: src/DGP/Error.hpp src/DGP/BasicStringAlg.hpp
src/DGP/Graphics/VAR.o: src/DGP/Log.hpp src/DGP/Noncopyable.hpp
src/DGP/Graphics/VAR.o: src/DGP/Spinlock.hpp src/DGP/StringAlg.hpp
src/DGP/Graphics/VAR.o: src/DGP/Common.hpp /usr/include/fnmatch.h
src/DGP/Graphics/VAR.o: src/DGP/Colors.hpp src/DGP/VectorN.hpp
src/DGP/Graphics/VAR.o: src/DGP/Graphics/GLHeaders.hpp src/DGP/FilePath.hpp
src/DGP/Graphics/VAR.o: src/DGP/Graphics/glew.hpp /usr/include/stdint.h
src/DGP/Graphics/VAR.o: /usr/include/features.h /usr/include/stdc-predef.h
src/DGP/Graphics/VAR.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/DGP/Graphics/VAR.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
src/DGP/Graphics/VAR.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
src/DGP/Graphics/VAR.o: src/DGP/Graphics/VARArea.hpp src/DGP/NamedObject.hpp
src/DGP/Graphics/VAR.o: src/DGP/Graphics/GLCaps.hpp
src/DGP/Graphics/VAR.o: src/DGP/Graphics/Texture.hpp src/DGP/Image.hpp
src/DGP/Graphics/VAR.o: src/DGP/IOStream.hpp src/DGP/BinaryInputStream.hpp
src/DGP/Graphics/VAR.o: src/DGP/Colors.hpp src/DGP/ColorL.hpp
src/DGP/Graphics/VAR.o: src/DGP/Math.hpp src/DGP/Random.hpp
src/DGP/Graphics/VAR.o: /usr/include/math.h /usr/include/bits/math-vector.h
src/DGP/Graphics/VAR.o: /usr/include/bits/libm-simd-decl-stubs.h
src/DGP/Graphics/VAR.o: /usr/include/bits/huge_val.h
src/DGP/Graphics/VAR.o: /usr/include/bits/huge_valf.h
src/DGP/Graphics/VAR.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/DGP/Graphics/VAR.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/DGP/Graphics/VAR.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/DGP/Graphics/VAR.o: src/DGP/ColorRGB.hpp src/DGP/Vector3.hpp
src/DGP/Graphics/VAR.o: src/DGP/Vector2.hpp src/DGP/VectorN.hpp
src/DGP/Graphics/VAR.o: src/DGP/Vector4.hpp src/DGP/ColorRGB8.hpp
src/DGP/Graphics/VAR.o: src/DGP/ColorRGBA.hpp src/DGP/ColorRGBA8.hpp
src/DGP/Graphics/VAR.o: src/DGP/CoordinateFrame3.hpp
src/DGP/Graphics/VAR.o: src/DGP/CoordinateFrameN.hpp
src/DGP/Graphics/VAR.o: src/DGP/RigidTransformN.hpp
src/DGP/Graphics/VAR.o: src/DGP/AffineTransformN.hpp src/DGP/MatrixMN.hpp
src/DGP/Graphics/VAR.o: src/DGP/AddressableMatrix.hpp
src/DGP/Graphics/VAR.o: src/DGP/IteratableMatrix.hpp src/DGP/BasicMatrix.hpp
src/DGP/Graphics/VAR.o: src/DGP/MatrixInvert.hpp src/DGP/MatrixInvertTmpl.hpp
src/DGP/Graphics/VAR.o: src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp
src/DGP/Graphics/VAR.o: src/DGP/Matrix4.hpp src/DGP/AffineTransform2.hpp
src/DGP/Graphics/VAR.o: src/DGP/AffineTransform3.hpp
src/DGP/Graphics/VAR.o: src/DGP/RigidTransform2.hpp
src/DGP/Graphics/VAR.o: src/DGP/RigidTransform3.hpp
src/DGP/Graphics/VAR.o: src/DGP/CoordinateFrame2.hpp src/DGP/NamedObject.hpp
src/DGP/Graphics/VAR.o: src/DGP/Plane3.hpp src/DGP/Hyperplane3.hpp
src/DGP/Graphics/VAR.o: src/DGP/HyperplaneN.hpp src/DGP/RayIntersectableN.hpp
src/DGP/Graphics/VAR.o: src/DGP/RayN.hpp src/DGP/Ray3.hpp
src/DGP/Graphics/VAR.o: src/DGP/RayIntersectable3.hpp
src/DGP/Graphics/VAR.o: src/DGP/BinaryOutputStream.hpp
src/DGP/Graphics/VAR.o: src/DGP/TextInputStream.hpp
src/DGP/Graphics/VAR.o: src/DGP/TextOutputStream.hpp src/DGP/Serializable.hpp
src/DGP/Graphics/VAR.o: src/DGP/Graphics/TextureFormat.hpp
src/main.o: src/Mesh.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/main.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/main.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/main.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/main.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/main.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/main.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/main.o: src/DGP/Graphics/RenderSystem.hpp src/DGP/Common.hpp
src/main.o: src/DGP/Camera.hpp src/DGP/Serializable.hpp src/DGP/IOStream.hpp
src/main.o: src/DGP/BinaryInputStream.hpp src/DGP/Colors.hpp
src/main.o: src/DGP/ColorL.hpp src/DGP/Math.hpp src/DGP/Random.hpp
src/main.o: /usr/include/math.h /usr/include/features.h
src/main.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/main.o: /usr/include/bits/math-vector.h
src/main.o: /usr/include/bits/libm-simd-decl-stubs.h
src/main.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/main.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/main.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/main.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/main.o: src/DGP/ColorRGB.hpp src/DGP/Vector3.hpp src/DGP/Vector2.hpp
src/main.o: src/DGP/VectorN.hpp src/DGP/Vector4.hpp src/DGP/ColorRGB8.hpp
src/main.o: src/DGP/ColorRGBA.hpp src/DGP/ColorRGBA8.hpp
src/main.o: src/DGP/CoordinateFrame3.hpp src/DGP/CoordinateFrameN.hpp
src/main.o: src/DGP/RigidTransformN.hpp src/DGP/AffineTransformN.hpp
src/main.o: src/DGP/MatrixMN.hpp src/DGP/AddressableMatrix.hpp
src/main.o: src/DGP/IteratableMatrix.hpp src/DGP/BasicMatrix.hpp
src/main.o: src/DGP/MatrixInvert.hpp src/DGP/MatrixInvertTmpl.hpp
src/main.o: src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp src/DGP/Matrix4.hpp
src/main.o: src/DGP/AffineTransform2.hpp src/DGP/AffineTransform3.hpp
src/main.o: src/DGP/RigidTransform2.hpp src/DGP/RigidTransform3.hpp
src/main.o: src/DGP/CoordinateFrame2.hpp src/DGP/NamedObject.hpp
src/main.o: src/DGP/Plane3.hpp src/DGP/Hyperplane3.hpp
src/main.o: src/DGP/HyperplaneN.hpp src/DGP/RayIntersectableN.hpp
src/main.o: src/DGP/RayN.hpp src/DGP/Ray3.hpp src/DGP/RayIntersectable3.hpp
src/main.o: src/DGP/BinaryOutputStream.hpp src/DGP/TextInputStream.hpp
src/main.o: src/DGP/TextOutputStream.hpp src/DGP/Colors.hpp src/DGP/Image.hpp
src/main.o: src/DGP/NamedObject.hpp src/DGP/Graphics/Framebuffer.hpp
src/main.o: src/DGP/Graphics/GLHeaders.hpp src/DGP/FilePath.hpp
src/main.o: src/DGP/Graphics/glew.hpp /usr/include/stdint.h
src/main.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
src/main.o: /usr/include/GL/gl.h src/DGP/Graphics/Texture.hpp
src/main.o: src/DGP/Graphics/TextureFormat.hpp src/DGP/Graphics/Shader.hpp
src/main.o: src/DGP/MatrixMN.hpp src/DGP/VectorN.hpp src/DGP/Graphics/VAR.hpp
src/main.o: src/DGP/Graphics/VARArea.hpp src/DGP/AxisAlignedBox3.hpp
src/main.o: src/DGP/AxisAlignedBoxN.hpp src/DGP/AxisAlignedBox3.hpp
src/main.o: src/DGP/Colors.hpp src/DGP/NamedObject.hpp
src/main.o: src/DGP/Noncopyable.hpp src/DGP/Vector3.hpp src/MeshFace.hpp
src/main.o: src/MeshVertex.hpp src/MeshEdge.hpp src/Viewer.hpp
src/main.o: src/DGP/Camera.hpp src/DGP/Matrix3.hpp
src/Mesh.o: src/Mesh.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/Mesh.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/Mesh.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/Mesh.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/Mesh.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/Mesh.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/Mesh.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/Mesh.o: src/DGP/Graphics/RenderSystem.hpp src/DGP/Common.hpp
src/Mesh.o: src/DGP/Camera.hpp src/DGP/Serializable.hpp src/DGP/IOStream.hpp
src/Mesh.o: src/DGP/BinaryInputStream.hpp src/DGP/Colors.hpp
src/Mesh.o: src/DGP/ColorL.hpp src/DGP/Math.hpp src/DGP/Random.hpp
src/Mesh.o: /usr/include/math.h /usr/include/features.h
src/Mesh.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
src/Mesh.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/Mesh.o: /usr/include/bits/math-vector.h
src/Mesh.o: /usr/include/bits/libm-simd-decl-stubs.h
src/Mesh.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/Mesh.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/Mesh.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/Mesh.o: /usr/include/bits/mathcalls.h src/DGP/ColorL8.hpp
src/Mesh.o: src/DGP/ColorRGB.hpp src/DGP/Vector3.hpp src/DGP/Vector2.hpp
src/Mesh.o: src/DGP/VectorN.hpp src/DGP/Vector4.hpp src/DGP/ColorRGB8.hpp
src/Mesh.o: src/DGP/ColorRGBA.hpp src/DGP/ColorRGBA8.hpp
src/Mesh.o: src/DGP/CoordinateFrame3.hpp src/DGP/CoordinateFrameN.hpp
src/Mesh.o: src/DGP/RigidTransformN.hpp src/DGP/AffineTransformN.hpp
src/Mesh.o: src/DGP/MatrixMN.hpp src/DGP/AddressableMatrix.hpp
src/Mesh.o: src/DGP/IteratableMatrix.hpp src/DGP/BasicMatrix.hpp
src/Mesh.o: src/DGP/MatrixInvert.hpp src/DGP/MatrixInvertTmpl.hpp
src/Mesh.o: src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp src/DGP/Matrix4.hpp
src/Mesh.o: src/DGP/AffineTransform2.hpp src/DGP/AffineTransform3.hpp
src/Mesh.o: src/DGP/RigidTransform2.hpp src/DGP/RigidTransform3.hpp
src/Mesh.o: src/DGP/CoordinateFrame2.hpp src/DGP/NamedObject.hpp
src/Mesh.o: src/DGP/Plane3.hpp src/DGP/Hyperplane3.hpp
src/Mesh.o: src/DGP/HyperplaneN.hpp src/DGP/RayIntersectableN.hpp
src/Mesh.o: src/DGP/RayN.hpp src/DGP/Ray3.hpp src/DGP/RayIntersectable3.hpp
src/Mesh.o: src/DGP/BinaryOutputStream.hpp src/DGP/TextInputStream.hpp
src/Mesh.o: src/DGP/TextOutputStream.hpp src/DGP/Colors.hpp src/DGP/Image.hpp
src/Mesh.o: src/DGP/NamedObject.hpp src/DGP/Graphics/Framebuffer.hpp
src/Mesh.o: src/DGP/Graphics/GLHeaders.hpp src/DGP/FilePath.hpp
src/Mesh.o: src/DGP/Graphics/glew.hpp /usr/include/stdint.h
src/Mesh.o: /usr/include/bits/wchar.h /usr/include/GL/glu.h
src/Mesh.o: /usr/include/GL/gl.h src/DGP/Graphics/Texture.hpp
src/Mesh.o: src/DGP/Graphics/TextureFormat.hpp src/DGP/Graphics/Shader.hpp
src/Mesh.o: src/DGP/MatrixMN.hpp src/DGP/VectorN.hpp src/DGP/Graphics/VAR.hpp
src/Mesh.o: src/DGP/Graphics/VARArea.hpp src/DGP/AxisAlignedBox3.hpp
src/Mesh.o: src/DGP/AxisAlignedBoxN.hpp src/DGP/AxisAlignedBox3.hpp
src/Mesh.o: src/DGP/Colors.hpp src/DGP/NamedObject.hpp
src/Mesh.o: src/DGP/Noncopyable.hpp src/DGP/Vector3.hpp src/MeshFace.hpp
src/Mesh.o: src/MeshVertex.hpp src/MeshEdge.hpp src/DGP/FilePath.hpp
src/MeshEdge.o: src/MeshEdge.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/MeshEdge.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/MeshEdge.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/MeshEdge.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/MeshEdge.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/MeshEdge.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/MeshEdge.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h src/MeshFace.hpp
src/MeshEdge.o: src/DGP/Colors.hpp src/DGP/Vector3.hpp src/MeshVertex.hpp
src/MeshEdge.o: src/DGP/Vector4.hpp src/DGP/Vector2.hpp src/DGP/VectorN.hpp
src/MeshEdge.o: src/DGP/Math.hpp src/DGP/Random.hpp /usr/include/math.h
src/MeshEdge.o: /usr/include/features.h /usr/include/stdc-predef.h
src/MeshEdge.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/MeshEdge.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/MeshEdge.o: /usr/include/bits/libm-simd-decl-stubs.h
src/MeshEdge.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/MeshEdge.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/MeshEdge.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/MeshEdge.o: /usr/include/bits/mathcalls.h src/DGP/Vector3.hpp
src/MeshEdge.o: src/DGP/Vector4.hpp
src/MeshFace.o: src/MeshFace.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/MeshFace.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/MeshFace.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/MeshFace.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/MeshFace.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/MeshFace.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/MeshFace.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/MeshFace.o: src/DGP/Colors.hpp src/DGP/Vector3.hpp src/MeshVertex.hpp
src/MeshVertex.o: src/MeshVertex.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/MeshVertex.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/MeshVertex.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/MeshVertex.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/MeshVertex.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/MeshVertex.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/MeshVertex.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/MeshVertex.o: src/DGP/Colors.hpp src/DGP/Vector3.hpp src/MeshEdge.hpp
src/MeshVertex.o: src/MeshFace.hpp
src/Viewer.o: src/Viewer.hpp src/DGP/Common.hpp src/DGP/Platform.hpp
src/Viewer.o: src/DGP/SymbolVisibility.hpp src/DGP/AtomicInt32.hpp
src/Viewer.o: src/DGP/NumericTypes.hpp src/DGP/CommonEnums.hpp
src/Viewer.o: src/DGP/EnumClass.hpp src/DGP/Error.hpp
src/Viewer.o: src/DGP/BasicStringAlg.hpp src/DGP/Log.hpp
src/Viewer.o: src/DGP/Noncopyable.hpp src/DGP/Spinlock.hpp
src/Viewer.o: src/DGP/StringAlg.hpp /usr/include/fnmatch.h
src/Viewer.o: src/DGP/AxisAlignedBox3.hpp src/DGP/AxisAlignedBoxN.hpp
src/Viewer.o: src/DGP/Math.hpp src/DGP/Random.hpp /usr/include/math.h
src/Viewer.o: /usr/include/features.h /usr/include/stdc-predef.h
src/Viewer.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/Viewer.o: /usr/include/gnu/stubs.h /usr/include/bits/math-vector.h
src/Viewer.o: /usr/include/bits/libm-simd-decl-stubs.h
src/Viewer.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/Viewer.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/Viewer.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/Viewer.o: /usr/include/bits/mathcalls.h src/DGP/RayIntersectableN.hpp
src/Viewer.o: src/DGP/RayN.hpp src/DGP/CoordinateFrameN.hpp
src/Viewer.o: src/DGP/RigidTransformN.hpp src/DGP/AffineTransformN.hpp
src/Viewer.o: src/DGP/MatrixMN.hpp src/DGP/AddressableMatrix.hpp
src/Viewer.o: src/DGP/IteratableMatrix.hpp src/DGP/BasicMatrix.hpp
src/Viewer.o: src/DGP/MatrixInvert.hpp src/DGP/MatrixInvertTmpl.hpp
src/Viewer.o: src/DGP/VectorN.hpp src/DGP/Vector2.hpp src/DGP/Vector3.hpp
src/Viewer.o: src/DGP/Vector4.hpp src/DGP/Matrix2.hpp src/DGP/Matrix3.hpp
src/Viewer.o: src/DGP/Matrix4.hpp src/DGP/AffineTransform2.hpp
src/Viewer.o: src/DGP/AffineTransform3.hpp src/DGP/RigidTransform2.hpp
src/Viewer.o: src/DGP/RigidTransform3.hpp src/DGP/CoordinateFrame2.hpp
src/Viewer.o: src/DGP/CoordinateFrame3.hpp src/DGP/Ray3.hpp
src/Viewer.o: src/DGP/RayIntersectable3.hpp src/DGP/AxisAlignedBox3.hpp
src/Viewer.o: src/DGP/Camera.hpp src/DGP/Matrix3.hpp
src/Viewer.o: src/DGP/Graphics/RenderSystem.hpp src/DGP/Common.hpp
src/Viewer.o: src/DGP/Camera.hpp src/DGP/Serializable.hpp
src/Viewer.o: src/DGP/IOStream.hpp src/DGP/BinaryInputStream.hpp
src/Viewer.o: src/DGP/Colors.hpp src/DGP/ColorL.hpp src/DGP/ColorL8.hpp
src/Viewer.o: src/DGP/ColorRGB.hpp src/DGP/ColorRGB8.hpp
src/Viewer.o: src/DGP/ColorRGBA.hpp src/DGP/ColorRGBA8.hpp
src/Viewer.o: src/DGP/NamedObject.hpp src/DGP/Plane3.hpp
src/Viewer.o: src/DGP/Hyperplane3.hpp src/DGP/HyperplaneN.hpp
src/Viewer.o: src/DGP/BinaryOutputStream.hpp src/DGP/TextInputStream.hpp
src/Viewer.o: src/DGP/TextOutputStream.hpp src/DGP/Colors.hpp
src/Viewer.o: src/DGP/Image.hpp src/DGP/NamedObject.hpp
src/Viewer.o: src/DGP/Graphics/Framebuffer.hpp src/DGP/Graphics/GLHeaders.hpp
src/Viewer.o: src/DGP/FilePath.hpp src/DGP/Graphics/glew.hpp
src/Viewer.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/Viewer.o: /usr/include/GL/glu.h /usr/include/GL/gl.h
src/Viewer.o: src/DGP/Graphics/Texture.hpp src/DGP/Graphics/TextureFormat.hpp
src/Viewer.o: src/DGP/Graphics/Shader.hpp src/DGP/MatrixMN.hpp
src/Viewer.o: src/DGP/VectorN.hpp src/DGP/Graphics/VAR.hpp
src/Viewer.o: src/DGP/Graphics/VARArea.hpp src/Mesh.hpp src/DGP/Colors.hpp
src/Viewer.o: src/DGP/NamedObject.hpp src/DGP/Noncopyable.hpp
src/Viewer.o: src/DGP/Vector3.hpp src/MeshFace.hpp src/MeshVertex.hpp
src/Viewer.o: src/MeshEdge.hpp src/DGP/Graphics/Shader.hpp
src/Viewer.o: /usr/include/GL/glut.h /usr/include/GL/freeglut_std.h
src/Viewer.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
src/Viewer.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
src/Viewer.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
src/Viewer.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/Viewer.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
src/Viewer.o: /usr/include/time.h /usr/include/sys/select.h
src/Viewer.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/Viewer.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/Viewer.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/Viewer.o: /usr/include/bits/stdlib-float.h
