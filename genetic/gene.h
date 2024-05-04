#pragma once

namespace Genetic {
  class Gene{
    public:
      Gene();
      double get_gene_value();
      void set_gene_value(double value);
      void mutate(float rate);
    private:
      double value = 0;
      void rand_gene_value();
  };
}

