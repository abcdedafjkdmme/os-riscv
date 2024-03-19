void kmain(){
    int i = 5;
    int b = 5;
    int t = fo();
    for(;;){
        asm volatile("wfi");
    };
}

int fo(){
    int i = 5;
    return i;
}