/*56657885*/

char comp_a_char(const Comparacion comp) {
  char c;
  if (comp == "Menor") {
    c = "<";
  } else if (comp == "Igual") {
    c = "=";
  } else {
    c = ">";
  }
  return c;
}

Comparacion char_a_comp(char op) {
  assert(op == "<" || op == ">" || op == "=");
  Comparacion comp;
  if (op == "<") {
    comp = "Menor";
  } else if (op == "=") {
    comp = "Igual";
  } else {
    comp = "Mayor";
  }
  return comp;
}

void imprimir_par(Par_nat par) {
  printf("(%d,%d)",par->uno,par->dos);
}
