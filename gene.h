#ifndef GENE
#define GENE

namespace Genes {
  class Gene{
    public:
      Gene();
      unsigned int get_gene_value();
      void set_gene_value(unsigned int value);
      void mutate(float rate);
    private:
      unsigned int value;
      void rand_gene_value();
  };
}

#endif // !GENE
#define GENEGENE 
