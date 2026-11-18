int& badReference(){int local=25;return local;}
int main(){int& value=badReference();return value;}