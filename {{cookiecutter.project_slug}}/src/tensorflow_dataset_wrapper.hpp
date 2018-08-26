#pragma once
#include "tensorflow/core/framework/common_shape_fns.h"
#include "tensorflow/core/framework/dataset.h"
#include "tensorflow/core/framework/op.h"
#include "tensorflow/core/framework/shape_inference.h"
#include <array>
#include <experimental/optional>
#include <string>


namespace tensorflow
{
namespace
{
struct DatasetImplBase_
{
    OpKernelConstruction* ctx;

    explicit DatasetImplBase_(OpKernelConstruction* ctx)
        : ctx(ctx)
    {}

    template <typename T>
    T get_attr(const std::string& attr_name)
    {
        T value;
        OP_REQUIRES_OK(ctx, ctx->GetAttr(attr_name, &value));
        return value;
    }
};


template <typename DatasetImpl>
class DatasetOp : public DatasetOpKernel
{
public:
    explicit DatasetOp(OpKernelConstruction* ctx)
        : DatasetOpKernel(ctx)
        , dataset_impl(ctx)
    {}

    void MakeDataset(OpKernelContext* ctx, DatasetBase** output) override
    {
        // Parse and validate any input tensors that define the dataset using
        // `ctx->input()` or the utility function
        // `ParseScalarArgument<T>(ctx, &arg)`.

        // Create the dataset object, passing any (already-validated) arguments from
        // attrs or input tensors.
        *output = new Dataset(ctx);
    }

    struct Dataset : GraphDatasetBase
    {
    public:
        const DatasetOp& dataset_op;

        Dataset(OpKernelContext* ctx)
            : GraphDatasetBase(ctx)
            , dataset_op(dynamic_cast<const DatasetOp&>(ctx->op_kernel()))
        {}

        std::unique_ptr<IteratorBase> MakeIteratorInternal(const std::string& prefix) const override
        {
            return std::unique_ptr<IteratorBase>(new Iterator({ this, strings::StrCat(prefix, "::Reader") }));
        }

        const DataTypeVector& output_dtypes() const override
        {
            static DataTypeVector* dtypes = this->dataset_op.dataset_impl.output_dtypes();
            return *dtypes;
        }

        const std::vector<PartialTensorShape>& output_shapes() const override
        {
            static std::vector<PartialTensorShape>* shapes
                = new std::vector<PartialTensorShape>((this->dataset_op.dataset_impl.output_shapes()));
            return *shapes;
        }

        std::string DebugString() const override
        {
            return this->dataset_op.dataset_impl.debug_string();
        }

        struct Iterator : DatasetIterator<Dataset>
        {
            explicit Iterator(const typename DatasetIterator<Dataset>::Params& params)
                : DatasetIterator<Dataset>(params)
                , index(0)
                , dataset_op(params.dataset->dataset_op)
            {}

            Status
            GetNextInternal(IteratorContext* ctx, std::vector<Tensor>* out_tensors, bool* end_of_sequence) override
            {
                auto out = this->dataset_op.dataset_impl.getitem(ctx, this->index++);
                if (this->index == this->dataset_op.dataset_impl.size())
                    this->index = 0;

                if (out)
                {
                    for (auto&& tensor : *out)
                        out_tensors->push_back(std::move(tensor));
                    *end_of_sequence = false;
                }
                else
                {
                    *end_of_sequence = true;
                }

                return Status::OK();
            }

            mutex mu_;
            uint64_t index GUARDED_BY(mu_);
            const DatasetOp& dataset_op;
        };
    };

    DatasetImpl dataset_impl;
};


}  // namespace
}  // namespace tensorflow
