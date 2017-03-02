#pragma once
#include "EasyCNN/Configure.h"
#include "EasyCNN/Layer.h"

namespace EasyCNN
{
	class DropoutLayer : public Layer
	{
		FRIEND_WITH_NETWORK
	public:
		DropoutLayer();
		DropoutLayer(const float _rate);
		virtual ~DropoutLayer();
	public:
		void setParamaters(const float _rate);
	protected:
		virtual std::string serializeToString() const override;
		virtual void serializeFromString(const std::string content) override;
		DECLARE_LAYER_TYPE;
		virtual std::string getLayerType() const override;
		virtual void solveInnerParams() override;
		virtual void forward(const std::shared_ptr<DataBucket> prevDataBucket, std::shared_ptr<DataBucket> nextDataBucket) override;
		virtual void backward(std::shared_ptr<DataBucket> prevDataBucket, const std::shared_ptr<DataBucket> nextDataBucket, std::shared_ptr<DataBucket>& nextDiffBucket) override;
	private:
		float rate = 0.5f;
		std::shared_ptr<ParamBucket> maskData;
	};
}