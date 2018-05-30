#include "tensorflow/core/framework/common_shape_fns.h"
#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/shape_inference.h"


// Register the op definition for {{ cookiecutter.cpp_kernel_name }}.
// Add any attrs and input tensors that define the op here.
REGISTER_OP("{{ cookiecutter.cpp_kernel_name }}")
    .Input("x: float32")
    .Output("y: float32")
    .Output("gradients: float32")
    // .SetIsStateful()
    .SetShapeFn([](::tensorflow::shape_inference::InferenceContext* ctx) {
        ctx->set_output(0, ctx->input(0));
        ctx->set_output(1, ctx->input(0));
        return ::tensorflow::Status::OK();
    });


namespace tensorflow
{
class {{ cookiecutter.cpp_kernel_name }}: public OpKernel
{
public:
    explicit {{ cookiecutter.cpp_kernel_name }}(OpKernelConstruction* ctx)
        : OpKernel(ctx)
    {}

    void Compute(OpKernelContext* ctx) override
    {
        const Tensor& input_tensor = ctx->input(0);
        auto input = input_tensor.flat<float>();

        Tensor* output_tensor = nullptr;
        OP_REQUIRES_OK(ctx, ctx->allocate_output(0, input_tensor.shape(), &output_tensor));
        auto output = output_tensor->flat<float>();

        const int N = input.size();
        for (int i = 0; i < N; i++)
            output(i) = input(i) * 2;

        Tensor* gradients_tensor = nullptr;
        OP_REQUIRES_OK(ctx, ctx->allocate_output("gradients", input_tensor.shape(), &gradients_tensor));
        auto gradients = gradients_tensor->flat<float>();
        gradients.setConstant(2.0f);
    }
};


// Register the kernel implementation for {{ cookiecutter.cpp_kernel_name }}.
REGISTER_KERNEL_BUILDER(Name("{{ cookiecutter.cpp_kernel_name }}").Device(DEVICE_CPU), {{ cookiecutter.cpp_kernel_name }});

}  // namespace tensorflow
