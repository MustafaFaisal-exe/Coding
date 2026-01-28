# =========================
# 1. Import libraries
# =========================

import numpy as np                  # Numerical operations
import pandas as pd                 # Data handling
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error


# =========================
# 2. Create sample data
# =========================
# Imagine this is housing data:
# size (in square feet) vs price (in $)

data = {
    "size_sqft": [500, 800, 1000, 1200, 1500, 1800, 2000],
    "price":     [50000, 80000, 100000, 120000, 150000, 180000, 200000]
}

# Convert dictionary to pandas DataFrame
df = pd.DataFrame(data)

print("Original Data:")
print(df)


# =========================
# 3. Prepare features & target
# =========================

# Feature (input): house size
X = df[["size_sqft"]]   # double brackets → keeps it as DataFrame

# Target (output): house price
y = df["price"]         # single bracket → Series


# =========================
# 4. Split data into training and testing sets
# =========================

X_train, X_test, y_train, y_test = train_test_split(
    X, y,
    test_size=0.2,      # 20% data for testing
    random_state=42     # reproducible results
)


# =========================
# 5. Train the ML model
# =========================

model = LinearRegression()   # Create model
model.fit(X_train, y_train) # Train model on training data


# =========================
# 6. Make predictions
# =========================

y_pred = model.predict(X_test)

print("\nPredicted prices:", y_pred)
print("Actual prices:", y_test.values)


# =========================
# 7. Evaluate the model
# =========================

mse = mean_squared_error(y_test, y_pred)
print("\nMean Squared Error:", mse)


# =========================
# 8. Predict price for a NEW house
# =========================

# New house size (1500 sqft)
new_house = np.array([[1500]])   # NumPy array (2D)

predicted_price = model.predict(new_house)
print("\nPredicted price for 1500 sqft house:", predicted_price[0])
