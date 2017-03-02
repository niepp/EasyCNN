#pragma once
#include <memory>
#include <vector>
#include "EasyCNN/Configure.h"
#include "EasyCNN/Layer.h"
#include "EasyCNN/LossFunction.h"
#include "EasyCNN/Optimizer.h"

namespace EasyCNN
{
	class NetWork
	{
	public:
		NetWork();
		virtual ~NetWork();
	public:
		//common
		float getLoss(const std::shared_ptr<EasyCNN::DataBucket> labelDataBucket, const std::shared_ptr<EasyCNN::DataBucket> outputDataBucket);
		//test only!
		bool loadModel(const std::string& modelFile);
		std::shared_ptr<EasyCNN::DataBucket> testBatch(const std::shared_ptr<DataBucket> inputDataBucket);
		//train only!
		void setInputSize(const DataSize size);
		void setLossFunctor(std::shared_ptr<LossFunctor> lossFunctor);
		void setOptimizer(std::shared_ptr<Optimizer> optimizer);
		void setLearningRate(const float lr);
		void addayer(std::shared_ptr<Layer> layer);
		float trainBatch(const std::shared_ptr<DataBucket> inputDataBucket,
			const std::shared_ptr<DataBucket> labelDataBucket);
		bool saveModel(const std::string& modelFile);
	private:
		//common
		void setPhase(Phase phase);
		Phase getPhase() const;
		std::string encrypt(const std::string& content);
		std::string decrypt(const std::string& content);
	private:
		//common
		std::shared_ptr<EasyCNN::DataBucket> forward(const std::shared_ptr<DataBucket> inputDataBucket);
		float backward(const std::shared_ptr<DataBucket> labelDataBucket);
		std::string serializeToString() const;
		std::vector<std::shared_ptr<EasyCNN::Layer>> serializeFromString(const std::string content);
		std::shared_ptr<EasyCNN::Layer> createLayerByType(const std::string layerType);
	private:
		Phase phase = Phase::Train;
		std::vector<std::shared_ptr<Layer>> layers;
		std::vector<std::shared_ptr<DataBucket>> dataBuckets;
		std::shared_ptr<LossFunctor> lossFunctor;
		std::shared_ptr<Optimizer> optimizer;
	};
}