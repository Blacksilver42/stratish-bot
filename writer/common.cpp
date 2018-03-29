bool isBold(char x){
    return (x == 'A' || x == 'E' || x == 'I' || x == 'O' || x == 'U' || x == 'Y' || x == '-');
}

bool isThin(char x){
    return ((!(isBold(x)) && (x >= 'A' && x <= 'Z')) || x == '_');
}
