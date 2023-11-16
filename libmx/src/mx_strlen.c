int mx_strlen(const char* s) {
    int i = 0;
    while(1) {
        if(s[i] != '\0') i++;
        else return i;
    }
}
