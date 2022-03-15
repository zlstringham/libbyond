include(FetchContent)

FetchContent_Declare(
  cpu_features
  GIT_REPOSITORY https://github.com/google/cpu_features.git
  GIT_TAG        8a494eb1e158ec2050e5f699a504fbc9b896a43b # v0.7.0
)
FetchContent_MakeAvailable(cpu_features)
