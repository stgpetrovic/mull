int bitwise_or_assign(int a, int b) {
  int c = a;
  c |= b;
  return c;
}

int main() {
  return !(bitwise_or_assign(1, 2) == 3);
}

// clang-format off

/**
RUN: cd %CURRENT_DIR
RUN: sed -e "s:%PWD:%S:g" %S/compile_commands.json.template > %S/compile_commands.json
RUN: cd %S && %clang_cxx %sysroot %pass_mull_ir_frontend -g %s -o %s-ir.exe | %filecheck %s --dump-input=fail --strict-whitespace --match-full-lines --check-prefix=CHECK-MUTATE

CHECK-MUTATE-NOT:{{^.*[Ee]rror.*$}}

CHECK-MUTATE:[info] Applying filter: junk (threads: 1)
CHECK-MUTATE:[debug] CXXJunkDetector: mutation "Bitwise Or-Assign to And-Assign": {{.*}}sample.cpp:3:5 (end: 3:7)

RUN: (unset TERM; %mull_runner -debug -reporters=IDE -ide-reporter-show-killed %s-ir.exe 2>&1; test $? = 0) | %filecheck %s --dump-input=fail --strict-whitespace --match-full-lines

CHECK:[info] Killed mutants (1/1):
CHECK:{{^.*}}sample.cpp:3:5: warning: Killed: Replaced |= with &= [cxx_or_assign_to_and_assign]{{$}}
CHECK:  c |= b;
CHECK:    ^
CHECK:[info] Mutation score: 100%
CHECK:[info] Total execution time: {{.*}}
CHECK-EMPTY:
**/
