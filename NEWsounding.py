import pandas as pd
import plotly.express as px

# Load the dataset
file_path = 'C:/Users/broan/Downloads/Data/NightFlight.csv'
df = pd.read_csv(file_path, low_memory=False)

# Clean column names
df.columns = df.columns.str.strip()

# Convert to numeric
df['GPS Latitude'] = pd.to_numeric(df['GPS Latitude'], errors='coerce')
df['GPS Longitude'] = pd.to_numeric(df['GPS Longitude'], errors='coerce')
df['GPS Altitude'] = pd.to_numeric(df['GPS Altitude'], errors='coerce')
df['Payload State'] = pd.to_numeric(df['Payload State'], errors='coerce')
df['Humidity'] = pd.to_numeric(df['Humidity'], errors='coerce')
df['Temperature'] = pd.to_numeric(df['Temperature'], errors='coerce')
df['Pressure'] = pd.to_numeric(df['Pressure'], errors='coerce')
df['Oxygen Concentration'] = pd.to_numeric(df['Oxygen Concentration'], errors='coerce')

# Convert altitude from meters to kilometers
df['GPS Altitude'] = df['GPS Altitude'] / 1000  # Convert to km

# Drop rows with invalid or missing values
df = df.dropna(subset=['GPS Latitude', 'GPS Longitude', 'GPS Altitude', 'Payload State', 
                       'Humidity', 'Temperature', 'Pressure', 'Oxygen Concentration'])
df = df[
    (df['GPS Altitude'] > 0) & 
    (df['GPS Latitude'] != 0) & 
    (df['GPS Longitude'] != 0)
]

# Function to create and save 3D plots for various variables
def create_3d_plot(variable, title, color_continuous_scale='twilight'):
    fig = px.scatter_3d(
        df, 
        x='GPS Latitude', 
        y='GPS Longitude', 
        z='GPS Altitude', 
        color=variable, 
        color_continuous_scale=color_continuous_scale,
        labels={'GPS Latitude': 'Latitude', 'GPS Longitude': 'Longitude', 'GPS Altitude': 'Altitude (km)', variable: variable},
        title=title,
        range_z=[0, 30]  # Set the altitude range from 0 to 30 km
    )
    file_path = f'C:/Users/broan/Downloads/3D_{variable}_Plot.html'
    fig.write_html(file_path)
    print(f"{variable} plot saved to {file_path}")

# Create 3D plots for different variables
create_3d_plot('Payload State', '3D Payload States (Altitude 0–30 km)')
create_3d_plot('Humidity', '3D Humidity (Altitude 0–30 km)')
create_3d_plot('Temperature', '3D Temperature (Altitude 0–30 km)')
create_3d_plot('Pressure', '3D Pressure (Altitude 0–30 km)')
create_3d_plot('Oxygen Concentration', '3D Oxygen Concentration (Altitude 0–30 km)')

