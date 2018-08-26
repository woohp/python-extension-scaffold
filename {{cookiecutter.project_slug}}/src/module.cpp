#include "tensorflow_dataset_wrapper.hpp"
using namespace std;
using namespace std::experimental;


namespace tensorflow
{
namespace
{

struct {{ cookiecutter.cpp_kernel_name }}Impl : DatasetImplBase_
{
    {{ cookiecutter.cpp_kernel_name }}Impl(OpKernelConstruction* ctx)
        : DatasetImplBase_(ctx)
    {
        // put any attr initialization here
    }

    size_t size() const
    {
        return 100;
    }

    optional<array<Tensor, 1>> getitem(IteratorContext* ctx, size_t index) const
    {
        if (index >= 32)
            return nullopt;

        Tensor out = Tensor(ctx->allocator({}), DT_INT32, { 8 });
        auto out_ = out.vec<int>();
        out_.setConstant(index);

        return array<Tensor, 1>{ out };
    }

    DataTypeVector* output_dtypes() const
    {
        return new DataTypeVector({ DT_INT32 });
    }

    vector<PartialTensorShape> output_shapes() const
    {
        return { { -1 } };
    }

    string debug_string() const
    {
        return "{{ cookiecutter.cpp_kernel_name }}DatasetOp::Dataset";
    }
};


// Register the op definition for {{ cookiecutter.cpp_kernel_name }}.
// Add any attrs and input tensors that define the op here.
REGISTER_OP("{{ cookiecutter.cpp_kernel_name }}Dataset")
    .Output("handle: variant")
    .SetIsStateful()
    .SetShapeFn(shape_inference::ScalarShape);


// Register the kernel implementation for {{ cookiecutter.cpp_kernel_name }}.
REGISTER_KERNEL_BUILDER(Name("{{ cookiecutter.cpp_kernel_name }}Dataset").Device(DEVICE_CPU), DatasetOp<{{ cookiecutter.cpp_kernel_name }}Impl>);

}  // namespace
}  // namespace tensorflow
