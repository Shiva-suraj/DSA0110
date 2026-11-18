int main(){int* memory=new int[100];memory[0]=7;return memory[0]==7?0:1;}
// Intentional leak for LeakSanitizer demonstration only.
