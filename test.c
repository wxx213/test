
void user_swap(int &a, int &b)
{
    int c;
    c = a;
    a = b;
    b = c;
}
int main(void)
{
	int x = 12, y = 16;
	user_swap(x, y);
	return 0;	
}
