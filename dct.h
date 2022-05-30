class DCT{
    public:

    void block_dct(unsigned char * input, double * output, int width, int height, int blocksize);
    double * TWOdim_naive_DCT(unsigned char * x, double * y, int size);


    private:
    void section_fct(unsigned char *x , double * y, int & width, int & height, int  & blocksize, int & block_x, int & block_y);
    void horizontal_fct_help(double ** input, double ** output, int N);
    void vertical_fct_help(double ** input, double ** output, int N);






};