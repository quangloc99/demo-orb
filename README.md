# Demo sử dụng ORB descriptor của ORB_SLAM

## Cài đặt và chạy DEMO
    $ cmake .
    $ make
    $ ./example

## Cách sử dụng ORBextractor
Gọi là "extractor" bởi vì ngoài lấy keypoint nó còn lấy cả descriptors nữa.
Class ORBextractor có constructor gồm 5 tham số:
```
int nfeatures, float scaleFactor, int nlevels, int iniThFAST, int minThFAST
```
- `nFeatures` là số feature muốn lấy, theo paper với ảnh có kích thước 640x480 thì lấy 1000.
- `iniThFAST` và `minThFAST`: đầu tiên matching sẽ tìm các fast feature với threshold là `iniThFAST`,
  nếu số feature không thể đạt được `nFeatures`, extractor sẽ sử dụng `minThFAST` để tăng số
  feature lên.
- `scaleFactor` và `nLevels` hiện tại em vẫn chưa biết là gì :p, tuy nhiên trong ORB_SLAM1, 2 số này
được đặt default lần lượt là `1.2` và `8`.

Class có 1 method chính là
```
void operator()(
  cv::InputArray image,
  cv::InputArray mask,
  std::vector<cv::KeyPoint>& keypoints,
  cv::OutputArray descriptors
);
```
- `image` là ảnh được sử dụng để lấy keypoints và descriptors.
- `mask` là mask để giới hạn vùng ảnh, tuy nhiên theo comment, tham số này sẽ không được sử dụng. Khi sử 
dụng ta truyền vào noArray().
- 2 tham số cuối là output. Lưu ý descriptor có kiểu cho 1 ô là `32SC1`

## Tính hiệu quả
- Chất lượng: với threshold khoảng cách khoảng 50 và đặt camera ở xa vật thì
việc matching khá chính xác, tuy nhiên nếu camera quay nhanh thì có nhiều nhiễu.
- Tốc độ: với 1000 KeyPoints riêng phần lấy descriptor chạy trong treen 80ms, có khi lên đến
150ms. Ngoài ra phần matching theo cách của opencv cũng rất lâu, vào khoảng 100ms.
