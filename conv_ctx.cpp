// Auto generated by utensor-cli

#include "uTensor/ops/ArrayOps.hpp"
#include "conv_ctx.hpp"
#include "uTensor/core/tensor.hpp"
#include "uTensor/loaders/tensorIdxImporter.hpp"
#include "uTensor/core/context.hpp"
#include "uTensor/ops/MatrixOps.hpp"
#include "uTensor/ops/MathOps.hpp"


void get_test_quant_conv_ctx(Context& ctx) {
{
    TensorIdxImporter t_import;
    ctx.add(t_import.ubyte_import("/fs/idx_data/x_quint8_const_0.idx"),
            "x_quint8_const:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.ubyte_import("/fs/idx_data/w_filter_quint8_const_0.idx"),
            "w_filter_quint8_const:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/idx_data/x_min_0.idx"),
            "x_min:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/idx_data/x_max_0.idx"),
            "x_max:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/idx_data/w_filter_min_0.idx"),
            "w_filter_min:0",
            1);
}
{
    TensorIdxImporter t_import;
    ctx.add(t_import.float_import("/fs/idx_data/w_filter_max_0.idx"),
            "w_filter_max:0",
            1);
}
{
    ctx.add(new RamTensor<float>(), "out_conv_eightbit_quantized_conv:0", 2);
    ctx.add(new RamTensor<float>(), "out_conv_eightbit_quantized_conv:1", 2);
    ctx.add(new RamTensor<float>(), "out_conv_eightbit_quantized_conv:2", 2);
    ctx.push(new QntConvOp<uint8_t, uint8_t, float>({ 1, 2, 2, 1 }, VALID), 
             { "x_quint8_const:0", "w_filter_quint8_const:0", "x_min:0", "x_max:0", "w_filter_min:0", "w_filter_max:0" },
             { "out_conv_eightbit_quantized_conv:0", "out_conv_eightbit_quantized_conv:1", "out_conv_eightbit_quantized_conv:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>({1}), "out_conv_eightbit_requant_range:0", 1);
    ctx.add(new RamTensor<float>({1}), "out_conv_eightbit_requant_range:1", 1);
    ctx.push(new Requantization_RangeOp(),
             { "out_conv_eightbit_quantized_conv:0", "out_conv_eightbit_quantized_conv:1", "out_conv_eightbit_quantized_conv:2" },
             { "out_conv_eightbit_requant_range:0", "out_conv_eightbit_requant_range:1" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<uint8_t>(), "out_conv_eightbit_requantize:0", 1);
    ctx.add(new RamTensor<float>({1}), "out_conv_eightbit_requantize:1", 1);
    ctx.add(new RamTensor<float>({1}), "out_conv_eightbit_requantize:2", 1);
    ctx.push(new RequantizeOp(),
             { "out_conv_eightbit_quantized_conv:0", "out_conv_eightbit_quantized_conv:1", "out_conv_eightbit_quantized_conv:2", "out_conv_eightbit_requant_range:0", "out_conv_eightbit_requant_range:1" },
             { "out_conv_eightbit_requantize:0", "out_conv_eightbit_requantize:1", "out_conv_eightbit_requantize:2" });
    ctx.eval();
}
{
    ctx.add(new RamTensor<float>(), "out_conv:0");
    ctx.push(new DequantizeOp(), 
             { "out_conv_eightbit_requantize:0", "out_conv_eightbit_requantize:1", "out_conv_eightbit_requantize:2" },
             { "out_conv:0" });
}
}