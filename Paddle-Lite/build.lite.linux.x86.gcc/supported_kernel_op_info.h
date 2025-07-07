
// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once
#include<vector>
#include<map>
#include<string>

const std::vector<std::vector<std::string>> supported_ops_target = {

    // kUnk_OPS: 
    {"io_copy_once","io_copy","depthwise_conv2d_transpose","calib_inplace","layout","shuffle_channel","affine_channel","affine_grid","conv3d","prelu","thresholded_relu","elu","erf","softplus","subgraph","bmm","pad2d","grid_sampler","flatten_contiguous_range","layout_once"},

    // kHost_OPS: 
    {"flatten2","multiclass_nms2","cast","expand_as","feed","range","reshape","unsqueeze2","multiclass_nms","lod_array_length","prior_box","split","stack","yolo_box","unsqueeze","box_coder","fill_constant","squeeze","arg_max","expand","unbind","write_back","multiclass_nms3","flatten","squeeze2","fetch","fill_constant_batch_size_like","reshape2","assign_value"},

    // kX86_OPS: 
    {"slice","fusion_elementwise_max_activation","dropout","search_seq_arithmetic","transpose2","matmul","depthwise_conv2d","gru_unit","softmax","reduce_prod","softsign","stack","sequence_reverse","search_grnn","calib_once","search_seq_softmax","hard_swish","fusion_elementwise_min_activation","sigmoid","reduce_max","fc","sequence_pool","search_fc","batch_norm","elementwise_pow","elementwise_max","tanh","elementwise_div","var_conv_2d","layer_norm","sequence_concat","sync_batch_norm","elementwise_min","sequence_topk_avg_pooling","mul","fusion_elementwise_mul_activation","density_prior_box","sequence_conv","scale","mish","elementwise_sub","square","group_norm","conv2d_transpose","matmul_v2","elementwise_mul","search_seq_depadding","sequence_expand_as","fusion_elementwise_div_activation","relu6","nearest_interp_v2","reduce_min","elementwise_floordiv","box_coder","concat","elementwise_mod","search_group_padding","elementwise_add","bilinear_interp","bilinear_interp_v2","gelu","set_value","match_matrix_tensor","fusion_elementwise_add_activation","leaky_relu","rnn","rsqrt","sqrt","reduce_sum","lookup_table","lookup_table_v2","conv2d","nearest_interp","sequence_reshape","relu","fusion_elementwise_sub_activation","gru","transpose","pool2d","instance_norm","reduce_mean","search_attention_padding_mask","calib","sequence_arithmetic"},

    // kARM_OPS: 
    {"yolo_box","prior_box"},

    // kOpenCL_OPS: 
    {},
    // kAny_OPS: 
    {},
    // kXPU_OPS: 
    {},
    // kMetal_OPS: 
    {},
    // kNNAdapter_OPS: 
    {},};
const std::map<std::string, std::vector<std::string>> supported_ops={
    {"fill_constant", { "kHost" }},
    {"sequence_topk_avg_pooling", { "kX86" }},
    {"io_copy_once", { "kUnk" }},
    {"io_copy", { "kUnk" }},
    {"assign_value", { "kHost" }},
    {"unsqueeze", { "kHost" }},
    {"unsqueeze2", { "kHost" }},
    {"slice", { "kX86" }},
    {"expand_as", { "kHost" }},
    {"conv2d_transpose", { "kX86" }},
    {"depthwise_conv2d_transpose", { "kUnk" }},
    {"calib_inplace", { "kUnk" }},
    {"reduce_mean", { "kX86" }},
    {"layout", { "kUnk" }},
    {"shuffle_channel", { "kUnk" }},
    {"transpose", { "kX86" }},
    {"transpose2", { "kX86" }},
    {"affine_channel", { "kUnk" }},
    {"affine_grid", { "kUnk" }},
    {"lod_array_length", { "kHost" }},
    {"search_fc", { "kX86" }},
    {"dropout", { "kX86" }},
    {"scale", { "kX86" }},
    {"multiclass_nms", { "kHost" }},
    {"multiclass_nms2", { "kHost" }},
    {"multiclass_nms3", { "kHost" }},
    {"conv2d", { "kX86" }},
    {"conv3d", { "kUnk" }},
    {"depthwise_conv2d", { "kX86" }},
    {"nearest_interp", { "kX86" }},
    {"bilinear_interp", { "kX86" }},
    {"bilinear_interp_v2", { "kX86" }},
    {"nearest_interp_v2", { "kX86" }},
    {"box_coder", { "kHost", "kX86" }},
    {"arg_max", { "kHost" }},
    {"fetch", { "kHost" }},
    {"set_value", { "kX86" }},
    {"matmul", { "kX86" }},
    {"fc", { "kX86" }},
    {"expand", { "kHost" }},
    {"reshape", { "kHost" }},
    {"reshape2", { "kHost" }},
    {"range", { "kHost" }},
    {"yolo_box", { "kHost", "kARM" }},
    {"split", { "kHost" }},
    {"fusion_elementwise_sub_activation", { "kX86" }},
    {"fusion_elementwise_add_activation", { "kX86" }},
    {"fusion_elementwise_mul_activation", { "kX86" }},
    {"fusion_elementwise_max_activation", { "kX86" }},
    {"fusion_elementwise_min_activation", { "kX86" }},
    {"fusion_elementwise_div_activation", { "kX86" }},
    {"stack", { "kHost", "kX86" }},
    {"elementwise_sub", { "kX86" }},
    {"elementwise_add", { "kX86" }},
    {"elementwise_mul", { "kX86" }},
    {"elementwise_max", { "kX86" }},
    {"elementwise_min", { "kX86" }},
    {"elementwise_div", { "kX86" }},
    {"elementwise_floordiv", { "kX86" }},
    {"elementwise_mod", { "kX86" }},
    {"elementwise_pow", { "kX86" }},
    {"calib", { "kX86" }},
    {"sigmoid", { "kX86" }},
    {"tanh", { "kX86" }},
    {"relu", { "kX86" }},
    {"leaky_relu", { "kX86" }},
    {"relu6", { "kX86" }},
    {"prelu", { "kUnk" }},
    {"thresholded_relu", { "kUnk" }},
    {"elu", { "kUnk" }},
    {"erf", { "kUnk" }},
    {"softplus", { "kUnk" }},
    {"prior_box", { "kHost", "kARM" }},
    {"squeeze", { "kHost" }},
    {"squeeze2", { "kHost" }},
    {"pool2d", { "kX86" }},
    {"subgraph", { "kUnk" }},
    {"bmm", { "kUnk" }},
    {"write_back", { "kHost" }},
    {"instance_norm", { "kX86" }},
    {"fill_constant_batch_size_like", { "kHost" }},
    {"pad2d", { "kUnk" }},
    {"density_prior_box", { "kX86" }},
    {"cast", { "kHost" }},
    {"grid_sampler", { "kUnk" }},
    {"flatten", { "kHost" }},
    {"flatten2", { "kHost" }},
    {"flatten_contiguous_range", { "kUnk" }},
    {"concat", { "kX86" }},
    {"unbind", { "kHost" }},
    {"feed", { "kHost" }},
    {"mul", { "kX86" }},
    {"batch_norm", { "kX86" }},
    {"sync_batch_norm", { "kX86" }},
    {"layout_once", { "kUnk" }},
    {"softmax", { "kX86" }}
};