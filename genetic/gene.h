#pragma once

namespace Genes {
  class Gene{
    public:
      Gene();
      int get_gene_value();
      void set_gene_value(int value);
      void mutate(float rate);
    private:
      int value=0;
      void rand_gene_value();
  };
}

