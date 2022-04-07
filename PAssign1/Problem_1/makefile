SRC = src
CLASSPATH = bin
JC = javac
JFLAGS = -d $(CLASSPATH) -classpath $(SRC)
JVM = java
JVMFLAGS = -classpath $(CLASSPATH)
FILE =
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java
CLASSES = \
	$(SRC)/Producer.java \
	$(SRC)/Consumer.java \
	$(SRC)/Driver.java

MAIN = Driver

default: classes

classes: $(CLASSES:.java=.class)

run: $(CLASSPATH)/$(MAIN).class
	$(JVM) $(JVMFLAGS) $(MAIN) $(FILE)

clean:
	$(RM) $(CLASSPATH)/*.class
