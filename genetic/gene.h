#pragma once

namespace Genes {
  class Gene{
    public:
      Gene();
      double get_gene_value();
      void set_gene_value(double value);
      void mutate(float rate);
      void operator= (double value);
      double operator+ (double value);
      double operator* (double value);
    private:
      double value = 0;
      void rand_gene_value();
  };
}

