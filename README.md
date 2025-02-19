[P1602R0](https://wg21.link/p1602r0) and the implementation of "g++ -fmodules -M" shine a light on how to use C++ modules and header units in Make. This is a demo I wrote to somehow prove it and provide a very basic skeleton.

Things You Should Know:

1. Only gcc is supported because only "g++ -fmodules -M" generates the module-compatible Make rules based on [P1602R0](https://wg21.link/p1602r0).

2. Current implementation doen't generate the "perfect" rules. When specify the module prerequisites of an object target x.o, it outputs something like "x.o: y.c++-module z.c++-module", which works but makes x.o always getting rebuilt. This is because *.c++-module targets are not actually files but a tricky workaround.

  However, this could be fixed, if a simple '|' is added to the generated rule - making it "x.o:| y.c++-module z.c++-module". I modified gcc on my local computer and it works great. I'm considering making a patch to gcc, but I'm super noob and I'm not sure. And it seems like they have some plans to use 'grouped targets' from Make 4.3 to do the trick instead.

3. Header units are bastards. They affect the prepocessor state and thus must be processed with caution. To avoid 'the worst scenario' (it's always those worst scenarios), this demo forces you to queue up the header units in depdendency order. If A.h depends on B.h, you must put B.h before A.h in the HEADER_UNITS variable. And the rest is taken care of. Could be improved, though.

4. There should be some script to automatically set CXX_STDMODULE. I didn't write one, though.

Other Words:

1. The project and every file it contains are distributed under GNU Affero General Public License.

2. Like I said, I'm super noob, C++-wise and Makefile-wise. So the sed command processing .d files is not perfect. And when you try to use 'make clean' it would try to make sure you've already built the whole program successfully. Really bad. But I'm super stupid and can't fix that.

3. All glory to Nathan Sidwell for writing [P1602R0](https://wg21.link/p1602r0) and implement "g++ -fmodules -M".
